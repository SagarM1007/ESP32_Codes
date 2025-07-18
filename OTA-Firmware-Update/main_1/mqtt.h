#ifndef MQTT_H
#define MQTT_H

#include <PubSubClient.h>
#include <WiFi.h>

extern const char* mqtt_topic_sub;
extern const char* mqtt_topic_pub;
extern const char* mqtt_topic_update;
extern const char* mqtt_topic_control;

extern const char* mqtt_topic_reboot;
extern const char* mqtt_topic_data;
extern const char* mqtt_topic_status;


extern const char* mqtt_server;
extern const int mqtt_port;


extern WiFiClient espClient;
extern PubSubClient client;

void setupMQTT(PubSubClient& client);
void handleMQTT(PubSubClient& client);
void reconnect(PubSubClient& client);
void mqttCallback(char* topic, byte* message, unsigned int length);
void publishMessage(PubSubClient& client, const char* topic, const String& payload);

#endif
