#ifndef TIMER2_TICK_H
#define	TIMER2_TICK_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern volatile uint8_t flag1ms;

void TIMER2_Init(void);

#endif