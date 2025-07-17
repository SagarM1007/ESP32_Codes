
#include "mqtt.h"

PubSubClient client;

// Global variables
String tenantId;
String deviceId;

String ssid;
String password;

String sensor1Name;
String sensor1Type;

String sensor2Name;
String sensor2Type;

float latitude;
float longitude;

// Metrics
float temperature;
String tempUnit;

float pressure;
String pressureUnit;

// Timestamp
String recordedAt;

const char* mqtt_server = "broker.hivemq.com"; // Replace with your broker
const int mqtt_port = 1883;
const char* mqtt_topic = "TENANT001/DEV-006/data"; // Your specific topic


void connectToMQTT(void) {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected.");
    } else {
      Serial.print("Failed. rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}


String buildPayload(void)
{
  String payload = "{";

  payload += "\"tenantId\":\"" + tenantId + "\",";
  payload += "\"deviceId\":\"" + deviceId + "\",";
  payload += "\"metaData\":{";
  payload += "\"sensors\":[";
  payload += "{\"name\":\"" + sensor1Name + "\",\"type\":\"" + sensor1Type + "\"},";
  payload += "{\"name\":\"" + sensor2Name + "\",\"type\":\"" + sensor2Type + "\"}";
  payload += "]},";

  payload += "\"location\":{";
  payload += "\"latitude\":" + String(latitude, 10) + ",";
  payload += "\"longitude\":" + String(longitude, 10);
  payload += "},";

  payload += "\"metrics\":[";
  payload += "{";
  payload += "\"metricName\":\"temp\",";
  payload += "\"metricValue\":" + String(temperature, 2) + ",";
  payload += "\"metricUnit\":\"" + tempUnit + "\",";
  payload += "\"recordedAt\":\"" + recordedAt + "\"";
  payload += "},";

  payload += "{";
  payload += "\"metricName\":\"pressure\",";
  payload += "\"metricValue\":" + String(pressure, 2) + ",";
  payload += "\"metricUnit\":\"" + pressureUnit + "\",";
  payload += "\"recordedAt\":\"" + recordedAt + "\"";
  payload += "}";

  payload += "]";

  payload += "}";

  return payload;
}
