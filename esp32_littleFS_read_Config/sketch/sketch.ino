#include <SPIFFS.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }

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

  // Allocate a buffer to store contents of the file.
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

  // Print JSON values
  Serial.println("===== Configuration Data =====");
  Serial.print("SSID: "); Serial.println(doc["ssid"].as<const char*>());
  Serial.print("Password: "); Serial.println(doc["password"].as<const char*>());
  Serial.print("MQTT Server: "); Serial.println(doc["mqtt_server"].as<const char*>());
  Serial.print("MQTT Port: "); Serial.println(doc["mqtt_port"].as<int>());
  Serial.print("MQTT Topic (Sub): "); Serial.println(doc["mqtt_topic_sub"].as<const char*>());
  Serial.print("MQTT Topic (Pub): "); Serial.println(doc["mqtt_topic_pub"].as<const char*>());

  Serial.print("Device ID: "); Serial.println(doc["device_id"].as<const char*>());
  Serial.print("Tenant ID: "); Serial.println(doc["tenant_id"].as<const char*>());
  Serial.print("Device Name: "); Serial.println(doc["device_name"].as<const char*>());
  Serial.print("Device Type: "); Serial.println(doc["device_type"].as<const char*>());
  Serial.print("Metric Name: "); Serial.println(doc["metric_name"].as<const char*>());
  Serial.print("Metric Value: "); Serial.println(doc["metric_value"].as<float>());
  Serial.print("Metric Unit: "); Serial.println(doc["metric_unit"].as<const char*>());
  Serial.print("Recorded At: "); Serial.println(doc["recorded_at"].as<const char*>());
  Serial.print("Location: "); Serial.println(doc["location"].as<const char*>());

  JsonObject meta = doc["meta"];
  Serial.print("Sensor Serial: "); Serial.println(meta["sensor_serial"].as<const char*>());
  Serial.print("Firmware: "); Serial.println(meta["firmware"].as<const char*>());

  JsonArray labels = meta["labels"];
  Serial.print("Labels: ");
  for (const char* label : labels) {
    Serial.print(label);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  // Nothing to do here
}
