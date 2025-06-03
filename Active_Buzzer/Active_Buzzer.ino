/*
// Active Buzzer
#define BUZZER_PIN 8  // Connect the signal pin to D8

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER_PIN, HIGH); // Turn buzzer ON
  delay(500);                    // Wait 1 second
  digitalWrite(BUZZER_PIN, LOW);  // Turn buzzer OFF
  delay(2000);                    // Wait 1 second
}
*/


#define BUZZER_PIN 8

// Notes and frequencies (in Hz)
#define NOTE_C  261
#define NOTE_D  294
#define NOTE_E  329
#define NOTE_F  349
#define NOTE_G  392
#define NOTE_A  440
#define NOTE_B  493
#define NOTE_C_HIGH 523

// Melody (Twinkle Twinkle Little Star)
int melody[] = {
  NOTE_C, NOTE_C, NOTE_G, NOTE_G, NOTE_A, NOTE_A, NOTE_G,
  NOTE_F, NOTE_F, NOTE_E, NOTE_E, NOTE_D, NOTE_D, NOTE_C,
  NOTE_G, NOTE_G, NOTE_F, NOTE_F, NOTE_E, NOTE_E, NOTE_D,
  NOTE_G, NOTE_G, NOTE_F, NOTE_F, NOTE_E, NOTE_E, NOTE_D,
  NOTE_C, NOTE_C, NOTE_G, NOTE_G, NOTE_A, NOTE_A, NOTE_G,
  NOTE_F, NOTE_F, NOTE_E, NOTE_E, NOTE_D, NOTE_D, NOTE_C
};

int noteDurations[] = {
  500, 500, 500, 500, 500, 500, 1000,
  500, 500, 500, 500, 500, 500, 1000,
  500, 500, 500, 500, 500, 500, 1000,
  500, 500, 500, 500, 500, 500, 1000,
  500, 500, 500, 500, 500, 500, 1000,
  500, 500, 500, 500, 500, 500, 1000
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Nothing here – plays once on startup
  for (int i = 0; i < sizeof(melody) / sizeof(int); i++) 
  {
    tone(BUZZER_PIN, melody[i], noteDurations[i]);
    delay(noteDurations[i] * 1.3);  // Slight pause between notes
    noTone(BUZZER_PIN);             // Stop tone before next
  }
  delay(3000);
}


