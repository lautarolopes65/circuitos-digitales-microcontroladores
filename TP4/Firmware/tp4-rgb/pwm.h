#ifndef PWM_H
#define PWM_H
#include <avr/io.h>
#include <avr/interrupt.h>
#define TOP 255

void PWM_Init(void);
void PWM_Set(uint8_t,uint8_t,uint8_t);

#endif