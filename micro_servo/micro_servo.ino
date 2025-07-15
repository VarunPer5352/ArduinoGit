#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);   // Attach servo to pin D9
  myServo.write(0);    // Start at 0 degrees
  delay(500);          // Give time to settle
}

void loop() {
  // Sweep from 0 to 180 smoothly
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(10);          // 15 ms delay gives smooth, natural movement
  }

  delay(1000);          // Optional pause at 180

  // Sweep back from 180 to 0 smoothly
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }

  delay(1000);          // Optional pause at 0
}
