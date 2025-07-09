#include <WiFi.h>
#include <HTTPClient.h>
#include <SPIFFS.h>

const char* ssid = "RedmiNote";            // Replace with your actual WiFi SSID
const char* password = "Sagar1007";        // Replace with your actual WiFi password

const char* jsonUrl = "http://example.com/config.json"; // Replace with your actual JSON file URL

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Download JSON and save to SPIFFS
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(jsonUrl);

    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();

      // Debug: Print received JSON
      Serial.println("Received JSON:");
      Serial.println(payload);

      // Save to SPIFFS
      File file = SPIFFS.open("/config.json", FILE_WRITE);
      if (!file) {
        Serial.println("Failed to open file for writing");
      } else {
        file.print(payload);
        file.close();
        Serial.println("JSON saved to /config.json");
      }

    } else {
      Serial.printf("HTTP GET failed, error: %d\n", httpCode);
    }

    http.end();
  }
}

void loop() {
  // nothing here 
}
