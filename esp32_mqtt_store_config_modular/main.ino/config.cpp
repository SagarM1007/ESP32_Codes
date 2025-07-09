#include "config.h"
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

// Define global variables here
String ssid;
String password;
String mqttServer;
int mqttPort;
String mqttTopicSub;
String mqttTopicPub;

String deviceId;
String tenantId;
String deviceName;
String deviceType;
String metricName;
float metricValue;
String metricUnit;
String recordedAt;
String location;

String sensorSerial;
String firmware;
std::vector<String> labels;

bool loadConfigFile(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = file.size();
  if (size > 4096) {
    Serial.println("Config file too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size + 1]);
  file.readBytes(buf.get(), size);
  buf[size] = '\0';

  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.print("Failed to parse config: ");
    Serial.println(error.c_str());
    return false;
  }

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

  return true;
}

void printConfig() {
  Serial.println("===== Configuration Data =====");
  Serial.printf("SSID: %s\n", ssid.c_str());
  Serial.printf("Password: %s\n", password.c_str());
  Serial.printf("MQTT Server: %s\n", mqttServer.c_str());
  Serial.printf("MQTT Port: %d\n", mqttPort);
  Serial.printf("MQTT Topic (Sub): %s\n", mqttTopicSub.c_str());
  Serial.printf("MQTT Topic (Pub): %s\n", mqttTopicPub.c_str());

  Serial.printf("Device ID: %s\n", deviceId.c_str());
  Serial.printf("Tenant ID: %s\n", tenantId.c_str());
  Serial.printf("Device Name: %s\n", deviceName.c_str());
  Serial.printf("Device Type: %s\n", deviceType.c_str());
  Serial.printf("Metric Name: %s\n", metricName.c_str());
  Serial.printf("Metric Value: %.2f\n", metricValue);
  Serial.printf("Metric Unit: %s\n", metricUnit.c_str());
  Serial.printf("Recorded At: %s\n", recordedAt.c_str());
  Serial.printf("Location: %s\n", location.c_str());

  Serial.printf("Sensor Serial: %s\n", sensorSerial.c_str());
  Serial.printf("Firmware: %s\n", firmware.c_str());

  Serial.print("Labels: ");
  for (const String& label : labels) {
    Serial.print(label + " ");
  }
  Serial.println();
}
