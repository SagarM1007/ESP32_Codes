#ifndef WIFI_CONFIGURATION_H
#define WIFI_CONFIGURATION_H

#include <WiFi.h>  // Ensure WiFi library is included

// Function declarations
void ConnectWifi();
bool connectToWiFi(const char* ssid, const char* password);

#endif // WIFI_CONFIGURATION_H
