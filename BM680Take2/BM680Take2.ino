// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include "Adafruit_BME680.h"

// // Create BME680 object
// Adafruit_BME680 bme;

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);
  
//   // Begin I2C communication
//   if (!bme.begin()) {
//     Serial.println("Could not find a valid BME680 sensor, check wiring!");
//     while (1);
//   }

//   // Set up oversampling and filter initialization
//   bme.setTemperatureOversampling(BME680_OS_8X);
//   bme.setHumidityOversampling(BME680_OS_2X);
//   bme.setPressureOversampling(BME680_OS_4X);
//   bme.setGasHeater(320, 150); // 320°C for 150 ms
// }

// void loop() {
//   // Perform measurement
//   if (!bme.performReading()) {
//     Serial.println("Failed to perform reading :(");
//     return;
//   }

//   // Print values
//   Serial.print("Temperature = ");
//   Serial.print(bme.temperature);
//   Serial.println(" *C");

//   Serial.print("Humidity = ");
//   Serial.print(bme.humidity);
//   Serial.println(" %");

//   Serial.print("Pressure = ");
//   Serial.print(bme.pressure / 100.0);
//   Serial.println(" hPa");

//   Serial.print("Gas = ");
//   Serial.print(bme.gas_resistance / 1000.0);
//   Serial.println(" KOhms");

//   Serial.println();
//   delay(2000); // Delay between readings
// }





#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

Adafruit_BME680 bme;
//(0x77); // Change to 0x76 if needed

float lastTemp = -999;
float threshold = 0.05; // Print if temp changes by this much

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!bme.begin()) {
    Serial.println("Could not find BME680, check wiring!");
    while (1);
  }

  // Only enable temp (others off to speed up)
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_NONE);
  bme.setPressureOversampling(BME680_OS_NONE);
  bme.setGasHeater(0, 0); // Turn off heater
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("Reading failed");
    return;
  }

  float t = bme.temperature;

  // Only print if temperature changed noticeably
  if (abs(t - lastTemp) > threshold) {
    Serial.print("Temperature: ");
    Serial.print(t, 2);
    Serial.println(" °C");
    lastTemp = t;
  }

  delay(200); // Fast update, smooth display
}
