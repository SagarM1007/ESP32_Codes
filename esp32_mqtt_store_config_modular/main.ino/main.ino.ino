#include <Arduino.h>
#include <SPIFFS.h>
#include "config.h"
#include "wifiConfiguration.h"

// Variables

//String ssid;
//String password;

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS mount failed.");
    return;
  }

  if (loadConfigFile()) {
    printConfig();
    Serial.println(".....................................................................");
    Serial.println("                            WIFI CONNECTION                          ");
    connectToWiFi(ssid,password);
    Serial.println(".....................................................................");
  } else {
    Serial.println("Failed to load config.");
  }
  
}

void loop() {
  // Your logic here


  delay(2000);
}
