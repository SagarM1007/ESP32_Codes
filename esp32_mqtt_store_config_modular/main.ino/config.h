#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <vector>

// Config variables (extern means they're defined elsewhere)
extern String ssid;
extern String password;
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

// Config functions
bool loadConfigFile(const char* path = "/config.json");

void printConfig();

#endif
