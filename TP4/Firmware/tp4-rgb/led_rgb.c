#include "led_rgb.h"

static struct{
	uint8_t r,g,b;
}led;

void LED_Init(void){
	led.r = 0;
	led.g = 0;
	led.b = 0;
}

void LED_SetRGB(uint8_t red,uint8_t green,uint8_t blue){
	led.r = red;
	led.g = green;
	led.b = blue;
	
	PWM_Set(led.r,led.g,led.b);
}

void LED_AplicarBrillo(uint8_t brillo){
	uint8_t r = ((uint16_t)led.r*brillo)/255;
	uint8_t g = ((uint16_t)led.g*brillo)/255;
	uint8_t b = ((uint16_t)led.b*brillo)/255;
	
	PWM_Set(r,g,b);
}