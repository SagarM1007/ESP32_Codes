#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#define CONFIG_PATH "/config.json"

void readConfig() {
  File file = SPIFFS.open(CONFIG_PATH, "r");
  if (!file) {
    Serial.println(" Failed to open config file");
    return;
  }

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();

  if (error) {
    Serial.print(" JSON deserialization failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Print all values
  serializeJsonPretty(doc, Serial);
  Serial.println();
}

void updateDeviceConfig(const char* newDeviceID, const char* newTenantID) {
  File file = SPIFFS.open(CONFIG_PATH, "r");
  if (!file) {
    Serial.println(" Cannot open config file for reading");
    return;
  }

  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, file);
  file.close();

  if (error) {
    Serial.print(" JSON deserialization failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Update fields
  doc["device_id"] = newDeviceID;
  doc["tenant_id"] = newTenantID;

  // Save the updated document
  file = SPIFFS.open(CONFIG_PATH, "w");
  if (!file) {
    Serial.println(" Cannot open config file for writing");
    return;
  }

  serializeJsonPretty(doc, file);
  file.close();

  Serial.println(" Config updated successfully.");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SPIFFS.begin(true)) {
    Serial.println(" Failed to mount SPIFFS");
    return;
  }

  Serial.println(" Reading current config:");
  readConfig();

  Serial.println("\n Updating config...");
  updateDeviceConfig("DEVICE501", "TENANT500");

  Serial.println("\n Reading updated config:");
  readConfig();
}

void loop() {
  // Nothing to do in loop
  for(int i = 0; i < 10; i++)
  {
    if(i % 2 == 0)
    {
      updateDeviceConfig("DEVICE501", "TENANT500");
      Serial.println("\n Reading updated config:");
      readConfig();
    }else{
      updateDeviceConfig("DEVICE200", "TENANT200");
      Serial.println("\n Reading updated config:");
      readConfig();
    }
  }

  delay(5000);
  
}
