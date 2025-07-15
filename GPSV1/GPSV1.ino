#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(4, 3); // RX = 4 (connect to GPS TX), TX = 3 (unused)
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);         // For Serial Monitor
  gpsSerial.begin(9600);      // For GPS Module
  Serial.println("GPS test started");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
    
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
    }
  }
}
