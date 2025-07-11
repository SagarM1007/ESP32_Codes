
#include "main.h"

// === Internal Config Parameters ===
// Define global variables here
String ssid;
String password;

String ssidCopy;
String passCopy;

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

const char* configPath = "/config.json";

String remoteConfigData;

bool fetchRemoteConfig(String &jsonContent) {
  HTTPClient http;
  http.begin(CONFIG_URL);
  int httpCode = http.GET();
  if (httpCode == 200) {
    jsonContent = http.getString();
    http.end();
    return true;
  }
  http.end();
  return false;
}

// === Update Internal Config If needed
bool updateConfigIfNeeded(const String &newConfig) {
  File file = SPIFFS.open("/config.json", "r");
  String existingConfig = file.readString();
  file.close();

  if (existingConfig != newConfig) {
    file = SPIFFS.open("/config.json", "w");
    file.print(newConfig);
    file.close();
    return true;  // Config updated
  }
  return false;  // No update
}

// === Load Internal Config File ===
bool loadConfigFile(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Failed to open config.json");
    return false;
  }

  size_t size = file.size();
  if (size > 4096) {
    Serial.println("Config file size is too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size + 1]);
  file.readBytes(buf.get(), size);
  buf[size] = '\0';

  //StaticJsonDocument<2048> doc;
  DynamicJsonDocument doc(2048); //
  DeserializationError error = deserializeJson(doc, buf.get());

  if (error) {
    Serial.print("Failed to parse config.json: ");
    Serial.println(error.c_str());
    return false;
  }

  // Store values into global variables
  ssid = doc["ssid"].as<String>();
  ssidCopy = ssid;
  password = doc["password"].as<String>();
  passCopy = password;
  
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

// === Print Internal Config Parameters 
void printConfig() {
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


void printRemoteJson(void)
{
  Serial.println(remoteConfigData);

  // Allocate enough memory for the JSON structure
  StaticJsonDocument<2048> doc;
  DeserializationError error = deserializeJson(doc, remoteConfigData);

  if (!error) {
    // Extract values
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

    // Print values
//    Serial.println("Parsed Remote Config:");
//    Serial.println("SSID: " + ssid);
//    Serial.println("Password: " + password);
//    Serial.println("Device ID: " + deviceId);
//    Serial.println("Tenant ID: " + tenantId);
//    Serial.println("Device Name: " + deviceName);
//    Serial.println("Device Type: " + deviceType);
//    Serial.println("MQTT Server: " + mqttServer);
//    Serial.println("MQTT Port: " + String(mqttPort));
//    Serial.println("Topic Pub: " + mqttTopicPub);
//    Serial.println("Topic Sub: " + mqttTopicSub);
  } else {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
  }
}
