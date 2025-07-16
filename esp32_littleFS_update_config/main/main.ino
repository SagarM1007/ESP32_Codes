#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <vector>
#include "main.h"
#include "wifiConfiguration.h"


String ssid = "";
String password = "";
String mqttServer = "";
int mqttPort = 1883;
String mqttTopicSub = "";
String mqttTopicPub = "";

String deviceId = "";
String tenantId = "";  
String deviceName = "";
String deviceType = "";
String metricName = "";
float metricValue = 0.0;
String metricUnit = "";
String recordedAt = "";
String location = "";

String sensorSerial = "";
String firmware = "";

std::vector<String> labels;


// ========== Setup ==========
void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }

  loadConfig();
  printConfig();
}

// ========== Loop ==========
void loop() {
  if(Serial.available() > 0)
  {
    String 
  }
  // Nothing to do here
}
