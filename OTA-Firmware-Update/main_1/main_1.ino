#include "main.h"

void setup() {
  Serial.begin(115200);
  ConnectWifi();
  // ==== Pheriph ====
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  client.setServer(mqtt_server, mqtt_port);  
  client.setCallback(mqttCallback);
  
}

void loop() {
  if (!client.connected()) {
    reconnect(client);  // ensures connection is maintained
  }
  
  client.loop();  // necessary to process MQTT traffic

}
