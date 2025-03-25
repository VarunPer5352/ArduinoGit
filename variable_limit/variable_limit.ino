#include "variable_limit.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(value);
  Serial.println(value1);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t static number = 100000;
  uint32_t double_number_value = double_number(number);
  Serial.print("The doubled number is = ");
  Serial.println(double_number_value);
  number++;
}

/*
* This function returns double the values input to it.
*/
uint32_t double_number(uint32_t number)
{
  return (2 * number);
}