#include <Keypad.h>
#include <stdint.h>
#include <string.h>

const char correct_password[] = "BACD#5311";
char entered_password[10];  // Stores the user input -> 9 characters{BACD#5311} + null terminator
uint8_t current_index = 0;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;

char hexaKeys[ROWS][COLS] = {  //Initialisation of a 2-D array
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

uint8_t row_pins[ROWS] = {9, 8, 7, 6}; // -> GPIOs man 9 is Digital Pin 9{~} same 8, 7, 6 & 5  
uint8_t col_pins[COLS] = {5, 4, 3, 2}; // -> same cols for digital pins

Keypad custom_keypad = Keypad(makeKeymap(hexaKeys), row_pins, col_pins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  char customKey = custom_keypad.getKey();

  if (customKey) 
  {
    Serial.print("Key Pressed: ");
    Serial.println(customKey);

    // Store the key
    if (current_index < 9) 
    {
      entered_password[current_index++] = customKey;
    }

    // When 9 characters are entered
    if (current_index == 9) 
    {
      entered_password[9] = '\0';  // Null-terminate

      if (strcmp(entered_password, correct_password) == 0) 
      {
        Serial.println("Password is correct");
        digitalWrite(13, HIGH);
        delay(1000);
      } else 
      {
        Serial.println("Wrong password");
      }

      // Reset
      current_index = 0;
      digitalWrite(13, LOW); // Glow On Board LED to show correct pwd has been entered.
    }
  }
}
