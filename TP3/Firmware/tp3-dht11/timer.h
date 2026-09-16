#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <avr/interrupt.h>
extern volatile uint32_t ticks10ms;

void TIMER_Init(void);

#endif