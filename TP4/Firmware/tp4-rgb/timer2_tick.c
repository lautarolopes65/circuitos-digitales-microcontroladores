#include "timer2_tick.h"
/*
	Timer utilizado para chequear ADC y actualizar MEF del efecto fade
	Interrupcion cada 1 ms
*/ 

volatile uint8_t flag1ms = 0;

void TIMER2_Init(void)
{
    // Modo CTC, 
    TCCR2A = (1<<WGM21);

    // Prescaler 64
    TCCR2B = (1<<CS22);

    /*
        16 MHz / 64 = 250 kHz
        OCR2A = 249
    */
    OCR2A = 249;
	
	// Interrupcion por COMPA
    TIMSK2 |= (1<<OCIE2A);
}

ISR(TIMER2_COMPA_vect)
{
	flag1ms = 1;
}