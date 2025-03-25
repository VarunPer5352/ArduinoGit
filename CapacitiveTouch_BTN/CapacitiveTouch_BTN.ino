// #define CAPACITIVE_BTN 7

// uint32_t count = 0;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   pinMode(CAPACITIVE_BTN, INPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if(digitalRead(CAPACITIVE_BTN))
//   {
//     //Means human contact with btn pressed/touched
//     Serial.print("Capacitive Button pressed -> ");
//     Serial.println(count);
//     count++;
//   }
// }

#define CAPACITIVE_BTN 7

uint32_t count = 0;
bool prevState = false;

void setup() {
  Serial.begin(9600);
  pinMode(CAPACITIVE_BTN, INPUT);
}

void loop() {
  bool currentState = digitalRead(CAPACITIVE_BTN);

  if (currentState && !prevState) {
    // Button just got pressed (rising edge)
    Serial.print("Capacitive Button pressed -> ");
    Serial.println(count++);
  }

  prevState = currentState;  // Update last state
}
