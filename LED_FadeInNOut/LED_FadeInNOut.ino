#include "led.h"

#define LED_GPIO 6

void setup()
{
  pinMode(LED_GPIO, OUTPUT);
}

void loop()
{
  led_fade(LED_GPIO, 16);
}

void led_fade(uint8_t pin_number,uint8_t fade_steps)
{
	for(;led_intensity <= 255; led_intensity += fade_steps)
    {
      analogWrite(pin_number, led_intensity);
      delay(500);
    }
  
	for(;led_intensity >= 0; led_intensity -= fade_steps)
    {
      analogWrite(pin_number, led_intensity);
      delay(500);
    }
}