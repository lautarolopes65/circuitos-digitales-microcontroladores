#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr\interrupt.h>
#include "lcd.h"
#include "teclado4x4.h"
#include "timer.h"
#include "mef.h"

void LEDS_Init();

#endif 