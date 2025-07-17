#include <WiFi.h>
#include "OTAUpdate.h"

const char *ssid = "Redmi";
const char *password = "Sagar3007";

// Replace this with your actual .bin firmware file URL
const String testFirmwareURL = "https://cdn-stg.shauryatechnosoft.com/cdn-content/cmcycyd0r0000ot93ac7e8wx4/cmcycyd0r0001ot9319colftd/configs/cmd5x71md001wdz9svnx0jojy.bin";
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
  delay(20000);
}
