#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
extern volatile uint16_t timeTicks;
extern volatile uint8_t flagMEF;
void TIMER_Init(void);
#endif