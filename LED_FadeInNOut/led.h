#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

uint16_t led_intensity = 0;

void led_fade(uint8_t pin_number,uint8_t fade_steps);

#endif // LED_H_INCLUDED
