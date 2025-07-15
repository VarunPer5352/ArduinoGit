#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)  // Adjust this for your altitude

Adafruit_BME280 bme;  // Default I2C address is 0x76

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!bme.begin(0x76)) {  // Try 0x77 if 0x76 fails
    Serial.println("Could not find BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("BME280 Initialized");
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature(), 2);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity(), 2);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F, 2);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA), 2);
  Serial.println(" m");

  Serial.println();
  delay(500); // Adjust as needed
}
