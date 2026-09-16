#ifndef LED_RGB_H
#define LED_RGB_H

#include "pwm.h"

void LED_Init(void);

void LED_SetRGB(uint8_t red,uint8_t green,uint8_t blue);

void LED_AplicarBrillo(uint8_t brillo);
#endif