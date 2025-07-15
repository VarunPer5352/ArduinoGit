// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BME280.h>
// #include <Adafruit_BMP280.h>

// Adafruit_BME280 bme;  // For BME280 (with humidity)
// Adafruit_BMP280 bmp;  // For BMP280 (no humidity)

// bool isBME = false;

// void setup() {
//   Serial.begin(9600);
//   delay(1000);
//   Serial.println("Searching for BMP280 or BME280...");

//   // First try BME280 at address 0x76
//   if (bme.begin(0x76)) {
//     isBME = true;
//     Serial.println("✅ BME280 detected at 0x76 (with humidity)");
//   }
//   // If not BME, try BMP280 at same address
//   else if (bmp.begin(0x76)) {
//     Serial.println("✅ BMP280 detected at 0x76 (NO humidity)");
//   }
//   else {
//     Serial.println("❌ No sensor found at 0x76. Check wiring.");
//     while (1); // Stop here
//   }
// }

// void loop() {
//   if (isBME) {
//     Serial.print("Temp: ");
//     Serial.print(bme.readTemperature());
//     Serial.print(" °C, Pressure: ");
//     Serial.print(bme.readPressure() / 100.0F);
//     Serial.print(" hPa, Humidity: ");
//     Serial.print(bme.readHumidity());
//     Serial.println(" %");
//   } else {
//     Serial.print("Temp: ");
//     Serial.print(bmp.readTemperature());
//     Serial.print(" °C, Pressure: ");
//     Serial.print(bmp.readPressure() / 100.0F);
//     Serial.println(" hPa");
//   }

//   delay(2000);
// }

/*
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  // Fastest possible config (less accurate but quick reaction)
  bmp.setSampling(
  Adafruit_BMP280::MODE_NORMAL,
  Adafruit_BMP280::SAMPLING_X1,
  Adafruit_BMP280::SAMPLING_X1,
  Adafruit_BMP280::FILTER_OFF,
  Adafruit_BMP280::STANDBY_MS_1   // Fastest supported by BMP280
);

  Serial.println("BMP280 ready for high-speed readings.");
}

void loop() {
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0F;

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C, Pressure: ");
  Serial.print(pres);
  Serial.println(" hPa");

  delay(200);  // Poll faster than usual
}
*/

#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

float currentTemp = 0.0;
float lastTemp = 0.0;
float baselineTemp = 0.0;

unsigned long stableStartTime = 0;
bool isStable = false;
bool baselineConfirmed = false;

const float STABILITY_THRESHOLD = 0.2; // ±0.2°C variation
const int STABILITY_TIME_MS = 5000;    // 5 seconds
const float DRIFT_THRESHOLD = 0.8;     // spike if > 0.8°C difference

void setup() {
  Serial.begin(9600);
  delay(1000);

  if (!bmp.begin(0x76)) {
    Serial.println("Sensor not found. Check wiring!");
    while (1);
  }

  // Fast config
  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X1,
    Adafruit_BMP280::SAMPLING_X1,
    Adafruit_BMP280::FILTER_OFF,
    Adafruit_BMP280::STANDBY_MS_1
  );

  Serial.println("BMP280 Smart Temp Monitor Ready...");
}

void loop() {
  currentTemp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;

  // --- Detect if temp is stable for a while ---
  if (!baselineConfirmed) {
    if (abs(currentTemp - lastTemp) <= STABILITY_THRESHOLD) {
      if (!isStable) {
        stableStartTime = millis();
        isStable = true;
      } else if (millis() - stableStartTime >= STABILITY_TIME_MS) {
        Serial.print("Stable temp detected: ");
        Serial.print(currentTemp);
        Serial.println(" °C");

        Serial.println("Confirm as baseline? Type 'Y' in Serial Monitor...");
        waitForConfirmation();  // wait for user input
      }
    } else {
      isStable = false;  // unstable again, reset timer
    }
  }
  else {
    // --- Compare with baseline ---
    float delta = currentTemp - baselineTemp;

    if (abs(delta) > DRIFT_THRESHOLD) {
      Serial.print("🚨 Temp change detected! Δ = ");
      Serial.print(delta, 2);
      Serial.print(" °C → New Temp: ");
      Serial.print(currentTemp);
      Serial.print(" °C, Pressure: ");
      Serial.print(pressure);
      Serial.println(" hPa");
    }
  }

  lastTemp = currentTemp;
  delay(200);
}

void waitForConfirmation() {
  while (!Serial.available()) {
    delay(100);
  }

  char userInput = Serial.read();
  if (userInput == 'Y' || userInput == 'y') {
    baselineTemp = currentTemp;
    baselineConfirmed = true;
    Serial.print("✅ Baseline temp locked at: ");
    Serial.print(baselineTemp);
    Serial.println(" °C");
    Serial.println("Now monitoring for spikes...");
  } else {
    Serial.println("❌ Not confirmed. Waiting for stability again...");
    isStable = false;
  }

  while (Serial.available()) Serial.read(); // Clear buffer
}
