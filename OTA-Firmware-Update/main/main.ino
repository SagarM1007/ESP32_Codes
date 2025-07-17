#include <WiFi.h>
#include "OTAUpdate.h"

const char *ssid = "Redmi";
const char *password = "Sagar3007";

// Replace this with your actual .bin firmware file URL
const String testFirmwareURL = "https://raw.githubusercontent.com/SagarM1007/ESP32_Codes/main/Blink.ino.esp32.bin";
int count = 0;
void setup()
{
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  //  performOTAUpdate(testFirmwareURL);
}

void loop()
{
  count++;
  Serial.print("Count: ");
  Serial.println(count);

  if (count == 3)
  {
    Serial.println("Remote Firmware going to update");
    performOTAUpdate(testFirmwareURL);
    
    count = 0;
  }
  delay(15000);
}
