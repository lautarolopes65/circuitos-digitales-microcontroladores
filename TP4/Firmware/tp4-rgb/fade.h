#ifndef FADE_H
#define FADE_H

#include <stdint.h>

typedef enum
{
	SUBIENDO,
	MAXIMO,
	BAJANDO,
	APAGADO
}estadoLed;

#define RAMPA_MS 1000
#define MAXIMO_MS 1000
#define LED_ON_MS 3000
#include "pwm.h"
#include "led_rgb.h"
void FADE_Init(void);

void FADE_Update(void);

void FADE_SetPeriodo(uint16_t T);

#endif