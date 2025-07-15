// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BME680.h>

// Adafruit_BME680 bme; // I2C

// float lastTemperature = 0;
// float threshold = 0.05; // Minimum change (°C) to consider as "visible" on serial

// void setup() {
//   Serial.begin(115200);
//   while (!Serial); // Wait for serial monitor (optional)
  
//   if (!bme.begin()) {
//     Serial.println("BME680 not found. Check wiring!");
//     while (1);
//   }

//   // Configure oversampling for accuracy & responsiveness
//   bme.setTemperatureOversampling(BME680_OS_8X);  // Highest precision
//   bme.setHumidityOversampling(BME680_OS_NONE);   // Skip other sensors
//   bme.setPressureOversampling(BME680_OS_NONE);
//   bme.setGasHeater(0, 0); // Turn off gas heater to save power and avoid heat interference
// }

// void loop() {
//   if (!bme.performReading()) {
//     Serial.println("Failed to read from BME680!");
//     delay(500);
//     return;
//   }

//   float temp = bme.temperature;

//   if (abs(temp - lastTemperature) > threshold) {
//     Serial.print("🌡️  Temp: ");
//     Serial.print(temp, 2);
//     Serial.println(" °C");

//     lastTemperature = temp;
//   }

//   delay(200); // Fast refresh, but not too fast to spam
// }


// #include <Wire.h>

// void setup() {
//   Wire.begin();
//   Serial.begin(115200);
//   while (!Serial);
//   Serial.println("I2C Scanner...");

//   for (byte addr = 1; addr < 127; addr++) {
//     Wire.beginTransmission(addr);
//     if (Wire.endTransmission() == 0) {
//       Serial.print("✅ Found device at 0x");
//       Serial.println(addr, HEX);
//     }
//   }
// }

// void loop() {}


// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BME680.h>

// // Create sensor object with default I2C address (0x76)
// //Adafruit_BME680 bme;
// Adafruit_BME680 bme(0x77); // 0x77 is the I2C secondary address

// void setup() {
//   Serial.begin(115200);
//   while (!Serial);  // Wait for Serial

//   Serial.println("BME680 Test");

//   if (!bme.begin()) {
//     Serial.println("BME680 not found. Check wiring, power, and I2C address!");
//     while (1); // Stop here if not found
//   }

//   Serial.println("BME680 found!");

//   // Minimal sensor setup: temperature only
//   bme.setTemperatureOversampling(BME680_OS_8X);
//   bme.setHumidityOversampling(BME680_OS_NONE);
//   bme.setPressureOversampling(BME680_OS_NONE);
//   bme.setGasHeater(0, 0); // Turn off heater
// }

// void loop() {
//   // Trigger reading
//   if (!bme.performReading()) {
//     Serial.println("Failed to perform reading");
//     delay(1000);
//     return;
//   }

//   // Print temperature
//   Serial.print("Temperature: ");
//   Serial.print(bme.temperature, 2);
//   Serial.println(" °C");

//   delay(1000);
// }
