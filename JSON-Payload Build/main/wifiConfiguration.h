#ifndef WIFI_CONFIGURATION_H
#define WIFI_CONFIGURATION_H

#include "main.h"

// Function declaration
void ConnectWifi(void);
bool connectToWiFi(const String &ssid, const String &password);

#endif
