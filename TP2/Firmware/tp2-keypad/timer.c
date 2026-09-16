#include "timer.h"

#include <avr/interrupt.h>
volatile uint16_t timeTicks = 0;
volatile uint8_t flagMEF;

void TIMER_Init(void)
{
	// Modo CTC
	TCCR0A |= (1 << WGM01);

	// Prescaler=64 
	TCCR0B |= (1 << CS01) | (1 << CS00);
	
    /*
        Frecuencia timer:

        16MHz / Prescaler(64) = 250000 Hz

        Tiempo por tick:
        1 / 250000 = 4 us

        Para 1 ms:

        1000 us / 4 us = 250 cuentas

        OCR0A = 249
    */
	// Valor de comparación
	OCR0A = 249;

	// Habilitar interrupción COMP A
	TIMSK0 |= (1 << OCIE0A);

	// Habilitar interrupciones globales
	sei();
}


ISR(TIMER0_COMPA_vect)
{
	timeTicks++;		//cada 1 ms
	flagMEF = 1;		//flag para MEF
}