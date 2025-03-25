#define ANALOG_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("The analog reading is:");
  Serial.println(analogRead(ANALOG_PIN));
  delay(500);
}

/*
void loop() {
    int adc_value = analogRead(A0);  // Read analog pin A0 (0-1023)
    float voltage = adc_value * (5.0 / 1023.0); // Convert to voltage
    Serial.print("ADC Value: ");
    Serial.print(adc_value);
    Serial.print(" | Voltage: ");
    Serial.println(voltage);
    delay(500);
}
*/