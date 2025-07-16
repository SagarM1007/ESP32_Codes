#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <vector>
#include "main.h"

// ========== Function to Load Config ==========
void loadConfig(void) {
  File file = SPIFFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Failed to open config.json");
    return;
  }

  size_t size = file.size();
  if (size > 4096) {
    Serial.println("Config file size is too large");
    return;
  }

  std::unique_ptr<char[]> buf(new char[size + 1]);
  file.readBytes(buf.get(), size);
  buf[size] = '\0';

  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.print("Failed to parse config.json: ");
    Serial.println(error.c_str());
    return;
  }

  // Store values into global variables
  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
  mqttServer = doc["mqtt_server"].as<String>();
  mqttPort = doc["mqtt_port"].as<int>();
  mqttTopicSub = doc["mqtt_topic_sub"].as<String>();
  mqttTopicPub = doc["mqtt_topic_pub"].as<String>();

  deviceId = doc["device_id"].as<String>();
  tenantId = doc["tenant_id"].as<String>();
  deviceName = doc["device_name"].as<String>();
  deviceType = doc["device_type"].as<String>();
  metricName = doc["metric_name"].as<String>();
  metricValue = doc["metric_value"].as<float>();
  metricUnit = doc["metric_unit"].as<String>();
  recordedAt = doc["recorded_at"].as<String>();
  location = doc["location"].as<String>();

  JsonObject meta = doc["meta"];
  sensorSerial = meta["sensor_serial"].as<String>();
  firmware = meta["firmware"].as<String>();

  JsonArray jsonLabels = meta["labels"];
  labels.clear();
  for (const char* label : jsonLabels) {
    labels.push_back(String(label));
  }
}

// ========== Function to Print Configuration ==========
void printConfig(void) {
  Serial.println("===== Configuration Data (From Global Variables) =====");
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("Password: "); Serial.println(password);
  Serial.print("MQTT Server: "); Serial.println(mqttServer);
  Serial.print("MQTT Port: "); Serial.println(mqttPort);
  Serial.print("MQTT Topic (Sub): "); Serial.println(mqttTopicSub);
  Serial.print("MQTT Topic (Pub): "); Serial.println(mqttTopicPub);

  Serial.print("Device ID: "); Serial.println(deviceId);
  Serial.print("Tenant ID: "); Serial.println(tenantId);
  Serial.print("Device Name: "); Serial.println(deviceName);
  Serial.print("Device Type: "); Serial.println(deviceType);
  Serial.print("Metric Name: "); Serial.println(metricName);
  Serial.print("Metric Value: "); Serial.println(metricValue);
  Serial.print("Metric Unit: "); Serial.println(metricUnit);
  Serial.print("Recorded At: "); Serial.println(recordedAt);
  Serial.print("Location: "); Serial.println(location);

  Serial.print("Sensor Serial: "); Serial.println(sensorSerial);
  Serial.print("Firmware: "); Serial.println(firmware);

  Serial.print("Labels: ");
  for (const String& label : labels) {
    Serial.print(label);
    Serial.print(" ");
  }
  Serial.println();
}
