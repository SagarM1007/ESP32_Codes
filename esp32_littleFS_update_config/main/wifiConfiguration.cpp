#include "wifiConfiguration.h"
#include "config.h"
#include <WiFi.h>

bool connectToWiFi(const String& ssid, const String& password) {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid.c_str(), password.c_str());

  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 10000; // 10 seconds timeout

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected successfully.");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("PASSWARD: ");
    Serial.println(password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("\nFailed to connect to WiFi.");
    return false;
  }
}
