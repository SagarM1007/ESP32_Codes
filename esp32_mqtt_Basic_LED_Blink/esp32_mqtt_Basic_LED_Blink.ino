#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Redmi";
const char* password = "Sagar3007";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* mqtt_topic_sub = "esp32/test/sub";
const char* mqtt_topic_pub = "esp32/test/pub";
const char* mqtt_topic_update = "esp32/test/update";
const char* mqtt_topic_reboot = "esp32/test/reboot";

#define LED_PIN_2 2 // LED PIN

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void publishMessage(PubSubClient& client, const char* topic, const String& payload) {
  if (client.connected()) {
    bool sent = client.publish(topic, payload.c_str());
    if (sent) {
      Serial.print("Published to ");
      Serial.print(topic);
      Serial.print(": ");
      Serial.println(payload);
    } else {
      Serial.println("Publish failed.");
    }
  } else {
    Serial.println("MQTT not connected. Cannot publish.");
  }
}


void callback(char* topic, byte* message, unsigned int length) {
  // Convert topic to String for easier comparison
  String topicStr = String(topic);

  // Convert message to String
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)message[i];
  }

  Serial.print("MQTT Message Received -> Topic: ");
  Serial.print(topicStr);
  Serial.print(", Message: ");
  Serial.println(msg);

  // === Topic 1 ===
  if (topicStr == "esp32/test/sub") {
    if (msg == "ON") {
      // Turn something ON
      digitalWrite(LED_PIN_2, HIGH);
      publishMessage(client, "esp32/test/pub", "LED Is ON");
      Serial.println("Turning ON device...");
    } else if (msg == "OFF") {
      // Turn something OFF
      digitalWrite(LED_PIN_2, LOW);
      publishMessage(client, "esp32/test/pub", "LED Is OFF");
      Serial.println("Turning OFF device...");
    } else {
      Serial.println("Unknown control command");
    }
  }

  // === Topic 2 ===
  else if (topicStr == "esp32/test/update") {
    if (msg.startsWith("http")) {
      publishMessage(client, "esp32/test/pub", "ESP32 Is Going to Update");
      Serial.println("Starting OTA update from URL: " + msg);
      // Trigger OTA update from URL
     // performOTAUpdate(msg);
    } else {
      Serial.println("Invalid OTA URL");
    }
  }

  // === Topic 3 ===
  else if (topicStr == "esp32/test/reboot") {
    if (msg == "now") {
      publishMessage(client, "esp32/test/reboot", "Reboot is going on");
      Serial.println("Reboot command received...");
      ESP.restart();
    }
  }

  // Add more topics as needed...
  else {
    Serial.println("Unhandled topic or message");
  }

  topicStr = "0";
  msg = "0";
}


void reconnect() {
  const char* clientId = "36a5b317-cf59-4df6-839c-7f13b850c18d";  // static ID same as MQTTBox
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_sub);
      client.subscribe(mqtt_topic_update);
      client.subscribe(mqtt_topic_reboot); // if needed
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
