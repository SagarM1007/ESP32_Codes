#ifndef OTAUPDATE_H
#define OTAUPDATE_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Update.h>
#include <WiFi.h>

void performOTAUpdate(const String& firmwareURL);

#endif
