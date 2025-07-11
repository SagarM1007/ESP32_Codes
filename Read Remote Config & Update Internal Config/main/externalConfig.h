
#ifndef EXTERNAL_CONFIG_H
#define EXTERNAL_CONFIG_H


bool fetchRemoteConfig(String &jsonContent);
// === Config File URL ===
#define CONFIG_URL "https://cdn-stg.shauryatechnosoft.com/cdn-content/cmcycyd0r0000ot93ac7e8wx4/cmcycyd0r0001ot9319colftd/configs/cmcycz1on0002ot93cymeqvif.json"
extern const char* configPath;

// === Internal Config Parameters ===
#include <vector>

// Config variables 
extern String ssid;
extern String password;

extern String ssidCopy;
extern String passCopy;
extern String mqttServer;
extern int mqttPort;
extern String mqttTopicSub;
extern String mqttTopicPub;

extern String deviceId;
extern String tenantId;
extern String deviceName;
extern String deviceType;
extern String metricName;
extern float metricValue;
extern String metricUnit;
extern String recordedAt;
extern String location;

extern String sensorSerial;
extern String firmware;
extern std::vector<String> labels;

//=== externalConfig.cpp functions ===
bool fetchRemoteConfig(String &jsonContent);
bool updateConfigIfNeeded(const String &newConfig);
bool loadConfigFile(const char* path = "/config.json");
void printConfig(void);

void printRemoteJson(void);

extern String remoteConfigData;

#endif
