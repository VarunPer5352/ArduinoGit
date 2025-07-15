// #include "DHT.h"

// #define DHTPIN 2        // Digital pin connected to DHT11
// #define DHTTYPE DHT11   // DHT 11

// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600);
//   dht.begin();
// }

// void loop() {
//   delay(2000);  // DHT11 has 1Hz sampling rate

//   float humidity = dht.readHumidity();
//   float temperature = dht.readTemperature(); // Celsius by default

//   if (isnan(humidity) || isnan(temperature)) {
//     Serial.println("Failed to read from DHT11!");
//     return;
//   }

//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.print(" %\t");
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.println(" *C");
// }


#include "DHT.h"

#define DHTPIN 2        // Digital pin connected to DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//  Declare reading number globally so it retains its value across loop() calls
uint32_t reading_num = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000); // DHT11 has 1Hz max sampling rate

  reading_num++;  //  Increment reading number

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("Reading ");
    Serial.print(reading_num);
    Serial.println(": Failed to read from DHT11!");
    return;
  }

  //  Print reading number along with sensor values
  Serial.print("Reading ");
  Serial.print(reading_num);
  Serial.print(": Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\tTemperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
}
