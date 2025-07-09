#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <LittleFS.h>  // or <FS.h> if older version

// Declare configuration variables
String ssid;
String password;
String mqtt_server;
int mqtt_port;
String mqtt_topic_sub;
String mqtt_topic_pub;


#define LED_PIN_2 2

WiFiClient espClient;
PubSubClient client(espClient);

void loadConfig() {
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  File file = LittleFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Failed to open config file");
    return;
  }

  size_t size = file.size();
  std::unique_ptr<char[]> buf(new char[size + 1]);
  file.readBytes(buf.get(), size);
  buf[size] = '\0';

  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Failed to parse config file");
    return;
  }

  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
  mqtt_server = doc["mqtt_server"].as<String>();
  mqtt_port = doc["mqtt_port"];
  mqtt_topic_sub = doc["mqtt_topic_sub"].as<String>();
  mqtt_topic_pub = doc["mqtt_topic_pub"].as<String>();
}

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void callback(char* topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  messageTemp.trim();

  if (messageTemp == "ON") {
    digitalWrite(LED_PIN_2, HIGH);
    Serial.println("LED turned ON");
  } else if (messageTemp == "OFF") {
    digitalWrite(LED_PIN_2, LOW);
    Serial.println("LED turned OFF");
  } else {
    Serial.println("Unknown command.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_sub.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN_2, OUTPUT);
  digitalWrite(LED_PIN_2, LOW);

  loadConfig();
  setup_wifi();

  client.setServer(mqtt_server.c_str(), mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
