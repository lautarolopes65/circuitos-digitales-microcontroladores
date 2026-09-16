#include "timer1.h"

/*
	TIMER 1
	PWM para PB1 Y PB2
 */

void TIMER1_Init(void)
{
 	    // Modo 5 Fast PWM 8 bits, prescaler 1024, modo no invertido
		//	f_pwm = 61.03 Hz
	    TCCR1A = (1 << WGM10) | (1 << COM1A1)  | (1 << COM1B1); 
	    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	 
	    OCR1A = 0;
	    OCR1B = 0;
}

