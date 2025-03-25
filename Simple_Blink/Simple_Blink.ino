uint32_t count = 0;
#define LED_GPIO PD4
#define ON_BOARD_LED PB5

void setup() {
    Serial.begin(9600);
    while (!Serial);  // Wait for Serial Monitor to open, i.e. unless the serial monitor is open get stuck in while loop
    Serial.println("MCU has been reset!");
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    count++;
    Serial.print("In the Loop ");Serial.print(count);Serial.println(" time!");  

    digitalWrite(LED_BUILTIN, HIGH);
    // if(digitalRead(LED_BUILTIN))
    // {
    //   Serial.println("LED is ON!");
    // }
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    // if(digitalRead(!LED_BUILTIN))
    // {
    //   Serial.println("LED is OFF!");
    // }
    delay(250);
}
