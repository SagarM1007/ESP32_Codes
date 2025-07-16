#include <FS.h>
#include <SPIFFS.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }

  File file = SPIFFS.open("/config.json", "r");
  if (file) {
    String content = file.readString();
    Serial.println("File Content: ");
    Serial.println(content);
    file.close();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
