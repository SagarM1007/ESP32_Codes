#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // UART1 on GPIO16 (RX), GPIO17 (TX)

float latitude = 0.0;
float longitude = 0.0;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
}

void loop() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();

      Serial.print("Latitude Variable: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude Variable: ");
      Serial.println(longitude, 6);
    }
  }
}
