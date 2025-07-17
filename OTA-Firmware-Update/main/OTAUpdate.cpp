#include "OTAUpdate.h"


void performOTAUpdate(const String& firmwareURL) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Aborting OTA.");
    return;
  }

  Serial.println("Starting OTA update...");

  WiFiClientSecure client;
  client.setInsecure(); //  Accepts any certificate — for dev/testing only =============================================> Red flag

  HTTPClient https;
  if (!https.begin(client, firmwareURL)) {
    Serial.println("HTTPS connection failed.");
    return;
  }

  int httpCode = https.GET();
  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("HTTP GET failed. Code: %d\n", httpCode);
    https.end();
    return;
  }

  int contentLength = https.getSize();
  if (contentLength <= 0) {
    Serial.println("Invalid content length.");
    https.end();
    return;
  }

  if (!Update.begin(contentLength)) {
    Serial.printf("Update.begin() failed. Error: %d\n", Update.getError());
    https.end();
    return;
  }

  WiFiClient* stream = https.getStreamPtr();
  size_t written = Update.writeStream(*stream);

  if (written != contentLength) {
    Serial.printf("Written only %d/%d bytes\n", (int)written, contentLength);
    https.end();
    return;
  }

  if (!Update.end()) {
    Serial.printf("Update.end() failed. Error: %d\n", Update.getError());
    https.end();
    return;
  }

  if (!Update.isFinished()) {
    Serial.println("Update incomplete.");
    https.end();
    return;
  }

  Serial.println("OTA update successful! Restarting...");
  delay(1000);
  ESP.restart();
}
