#ifndef MAIN_H
#define MAIN_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "uart.h"
#include "timer1.h"
#include "timer2_tick.h"
#include "terminal.h"
#include "pwm.h"
#include "adc.h"
#include "fade.h"
#include "led_rgb.h"

#endif