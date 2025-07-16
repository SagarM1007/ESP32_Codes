#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <vector>

// Internal Config File Parameters
extern String ssid;
extern String password;
extern String mqttServer;
extern int mqttPort;
extern String mqttTopicSub;
extern String mqttTopicPub;

// Device Information
extern String deviceId;
extern String tenantId;      
extern String deviceName;
extern String deviceType;
extern String metricName;
extern float metricValue;
extern String metricUnit;
extern String recordedAt;
extern String location;

// Meta Information
extern String sensorSerial;
extern String firmware;

extern std::vector<String> labels;



// internConfigOperations Functions Declrations
void printConfig(void);
void loadConfig(void);


// Device Pin Definitions
// define used ESP32 pins used in the project here

#endif // MAIN_H
