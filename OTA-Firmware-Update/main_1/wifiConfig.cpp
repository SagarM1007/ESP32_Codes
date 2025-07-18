#include "wifiConfig.h"

const char* ssid = "Redmi";
const char* password = "Sagar3007";

void ConnectWifi() {
    Serial.println("Connecting to WiFi...");

    if (WiFi.SSID() != ssid) {
        if (connectToWiFi(ssid, password)) {
            Serial.println("WiFi connected successfully using internal config.");
        }
    } else {
        Serial.println("Already connected to the correct WiFi.");
    }
}

bool connectToWiFi(const char* ssid, const char* password) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 10000; // 10 seconds timeout

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected successfully.");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("\nFailed to connect to WiFi.");
        return false;
    }
}
