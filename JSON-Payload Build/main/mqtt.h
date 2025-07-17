#ifndef MQTT_H
#define MQTT_H

#include "main.h"


// MQTT Broker
extern const char* mqtt_server = "broker.hivemq.com"; // Replace with your broker
extern const int mqtt_port = 1883;
extern const char* mqtt_topic = "TENANT001/DEV-006/data"; // Your specific topic

extern PubSubClient client;

void connectToMQTT();
void publishPayload(const String& payload);


// Global variables
extern String tenantId;
extern String deviceId;

extern String ssid;
extern String password;

extern String sensor1Name;
extern String sensor1Type;

extern String sensor2Name;
extern String sensor2Type;

extern float latitude;
extern float longitude;

// Metrics
extern float temperature;
extern String tempUnit;

extern float pressure;
extern String pressureUnit;

// Timestamp
extern String recordedAt;

void connectToMQTT(void);
String buildPayload(void);
#endif
