#include "main.h"

// MQTT Broker
const char *mqtt_server = "broker.hivemq.com"; // Replace with your broker
const int mqtt_port = 1883;
const char *mqtt_topic = "TENANT001/DEV-006/data"; // Your specific topic

void setup()
{
  Serial.begin(115200);
  ConnectWifi();
  client.setServer(mqtt_server, mqtt_port);
}



void loop()
{
  if (!client.connected())
  {
    connectToMQTT();
  }
  client.loop();

  tenantId = "TENANT001";
  deviceId = "TENANT001-DEV-006";

  sensor1Name = "s1";
  sensor1Type = "DHT22";

  sensor2Name = "s2";
  sensor2Type = "BMP180";

  latitude = 18.523324253520848;
  longitude = 73.85923332325768;

  temperature = 59.67;
  tempUnit = "C";

  pressure = 23.32;
  pressureUnit = "hPa";

  // Timestamp
  recordedAt = "2025-07-16T06:00:46.173717Z"; 

  String payload = buildPayload();

  // Publish to topic
  Serial.println(payload);

// boolean success = client.publish(mqtt_topic, payload.c_str());
//
//  if (success)
//  {
//    Serial.println("Payload published successfully.");
//  }
//  else
//  {
//    Serial.println("Failed to publish.");
//  }

  delay(5000); // Wait 5 seconds before next publish
}
