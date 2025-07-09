#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Redmi";
const char* password = "Sagar1007";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic_sub = "esp32/test/sub";
const char* mqtt_topic_pub = "esp32/test/pub";


#define LED_PIN_2 2

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  messageTemp.trim();  // remove \n or extra spaces
  Serial.println(messageTemp);

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
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  pinMode(LED_PIN_2, OUTPUT);
  digitalWrite(LED_PIN_2, LOW);
  
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
