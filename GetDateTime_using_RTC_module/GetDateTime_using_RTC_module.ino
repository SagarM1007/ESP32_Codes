#include <WiFi.h>
#include <Wire.h>
#include "RTClib.h"
#include <time.h>

const char* ssid     = "Redmi";
const char* password = "Sagar3007";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 19800; // for IST
const int   daylightOffset_sec = 0;


char recordedAt[40]; // ISO8601 string

RTC_DS3231 rtc;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Start I2C

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  unsigned long startAttempt = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected. Syncing time with NTP...");

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      // Convert to DateTime and set RTC
      rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                          timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));

      Serial.println("Time synced and saved to RTC:");
      Serial.println(&timeinfo, "Date: %Y-%m-%d  Time: %H:%M:%S");
    } else {
      Serial.println("Failed to sync time");
    }
  } else {
    Serial.println("\nWiFi not available. Reading time from RTC...");
  }

  // Print time from RTC
  DateTime now = rtc.now();
  Serial.printf("RTC Time: %04d-%02d-%02d %02d:%02d:%02d\n", now.year(), now.month(), now.day(),
                now.hour(), now.minute(), now.second());
}


void loop() {
  DateTime now = rtc.now();

  // Get simulated milliseconds
  uint16_t millisPart = millis() % 1000;

  // Format the ISO8601 string
  snprintf(recordedAt, sizeof(recordedAt),
           "%04d-%02d-%02dT%02d:%02d:%02d.%03dZ",
           now.year(), now.month(), now.day(),
           now.hour(), now.minute(), now.second(),
           millisPart);

  Serial.print("\"recordedAt\": \"");
  Serial.print(recordedAt);
  Serial.println("\"");

  delay(10000); // Every 10 seconds
}
