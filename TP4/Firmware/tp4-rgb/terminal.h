#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <stdint.h>
#include "uart.h"
#include "timer1.h"
#include "led_rgb.h"
#include "pwm.h"
#define BUFFER_CMD 25

void TERMINAL_Update(void);
void TERMINAL_ProcessCommand(void);

#endif