// PUSH BTN PULL DOWN CONFIG i.e. By default the GPIO input is LOW
// When we press BTN it will be High & the LED_BUILTIN should glow
#define PUSH_BTN 7

void setup()
{
  Serial.begin(115200);
  pinMode(PUSH_BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
 if(digitalRead(PUSH_BTN))
 {
  Serial.println("BTN Pressed!");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
 }
}