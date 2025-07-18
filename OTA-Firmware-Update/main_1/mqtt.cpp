#include "main.h"

const char* mqtt_topic_sub = "esp32/test/sub";
const char* mqtt_topic_pub = "esp32/test/pub";
const char* mqtt_topic_update = "esp32/test/update";
const char* mqtt_topic_control = "esp32/test/control";
const char* mqtt_topic_reboot = "esp32/test/reboot";
const char* mqtt_topic_data = "esp32/test/data";
const char* mqtt_topic_status = "esp32/test/status";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;




WiFiClient espClient;
PubSubClient client(espClient);


void mqttCallback(char* topic, byte* message, unsigned int length) {
  String topicStr = String(topic);
  String messageStr;

  for (int i = 0; i < length; i++) {
    messageStr += (char)message[i];
  }
  messageStr.trim();

  Serial.println("Message received:");
  Serial.println("Topic: " + topicStr);
  Serial.println("Payload: " + messageStr);

  if (topicStr == "esp32/test/reboot") {
    if (messageStr == "NOW") {
      publishMessage(client, "esp32/test/info", "ESP32 Rebooting...");
      Serial.println("Rebooting ESP...");
      ESP.restart();
    }
  } else if (topicStr == "esp32/test/sub") {
    if (messageStr == "ON") {
      Serial.println("LED On");
      digitalWrite(ledPin, HIGH);
      publishMessage(client, "esp32/test/info", "ESP32 LED is HIGH Now");      
    }else if (messageStr == "OFF") {
      Serial.println("LED OFF");
      digitalWrite(ledPin, LOW);
      publishMessage(client, "esp32/test/info", "ESP32 LED is Low Now");
    }
  }else if (topicStr == "esp32/test/update") {
    // Handle OTA update logic here
    Serial.println("Triggering OTA from MQTT");
    publishMessage(client, "esp32/test/info", "ESP32 Is Going to Update");
    performOTAUpdate(messageStr);  // assuming this function exists
  } else {
    Serial.println("Unknown topic, no action taken.");
  }
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


void reconnect(PubSubClient& client) {
  const char* clientId = "36a5b317-cf59-4df6-839c-7f13b850c18d";
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientId)) {
      Serial.println("connected");
      // Subscribe to all topics here
      client.subscribe(mqtt_topic_sub);
      client.subscribe(mqtt_topic_update);
      client.subscribe(mqtt_topic_control);
      client.subscribe(mqtt_topic_reboot);
      client.subscribe(mqtt_topic_data);
      client.subscribe(mqtt_topic_status);
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setupMQTT(PubSubClient& client) {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback);
}

void handleMQTT(PubSubClient& client) {
  if (!client.connected()) {
    reconnect(client);
  }
  client.loop();
}
