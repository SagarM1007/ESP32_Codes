#include "main.h"
#include <stdbool.h>

bool isLoadSuccess = false;
String inputCommand = "";

// ##############################  TEsting Functions  ############################

void ConnectWifi(void)
{
    // === Connect to the WIFI ===
    String currentSSID = WiFi.SSID();
    if (!(currentSSID == ssid))
    {
        if (connectToWiFi(ssid, password))
        {
            Serial.println("Wifi Connected Successfully Using Internal Config Parameters........");
        }
    }
}

void fetchLocalConfigJson(void)
{
    isLoadSuccess = loadConfigFile(configPath);
    if (isLoadSuccess)
    {
        Serial.println("Local config.json Loaded Success........");
        isLoadSuccess = false;
    }
    else
    {
        Serial.println("Local config.json Fetching error........");
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Below SPIFFS initialization is very impotant but should be after WIFI connections

    if (!SPIFFS.begin(true))
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }
}

void loop()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == '\n' || c == '\r')
        {
            inputCommand.trim(); // Remove whitespace or newline

            if (inputCommand.length() > 0)
            {
                Serial.println("Input Command: " + inputCommand);

                if (inputCommand == "1")
                {
                    fetchLocalConfigJson();
                    delay(200);

                    Serial.println("Fetched SSID: " + ssid);
                    Serial.println("Fetched PASSWORD: " + password);
                    ConnectWifi();
                }  else if (inputCommand == "2")
                {
                    if (fetchRemoteConfig(remoteConfigData))
                    {
                        Serial.println("Remote JSON Fetched Successfully...");
                    }
                    else
                    {
                        Serial.println("Remote Fetching Failed...");
                    }
                }
                else if (inputCommand == "3")
                {
                    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                    Serial.println("                Print Local Config  JSON               ");
                    printConfig();
                }
                else if (inputCommand == "4")
                {
                    Serial.println("Printing Remote JSON And Updating Local one..............");
                    printRemoteJson();
                }
                else if (inputCommand == "5")
                {
                    Serial.println("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
                    Serial.println("Updating Internal Config.json........ ");
                    if (updateConfigIfNeeded(remoteConfigData))
                    {
                        Serial.println("Internal config.json Updated Successfully...............");
                    }
                    else
                    {
                        Serial.println("Internal config.json Not Updated ...............");
                    }
                }
                else
                {
                    Serial.println("Unknown Command. Use 1, 2, 3, 4 or 5");
                }
            }

            inputCommand = ""; // Clear input after processing
        }
        else
        {
            inputCommand += c; // Append incoming character
        }
    }
}
