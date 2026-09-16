#include "timer.h"

volatile uint32_t ticks10ms = 0;

/*
	Interrupcion de timer1 cada 10 ms

 ticks10ms representa el tiempo transcurrido desde el arranque
 del sistema en unidades de 10 ms.
 
 ticks10ms = 100  -> pasó 1 segundo
 ticks10ms = 500  -> pasaron 5 segundos
 */
void TIMER_Init(void)
{
	// Modo CTC
	TCCR1B |= (1<<WGM12);

	// Prescaler=64 
	TCCR1B |= (1<<CS11)|(1<<CS10);
	
    /*
        Frecuencia timer:

        16MHz / Prescaler(64) = 250000 Hz

        Tiempo por tick:
        1 / 250000 = 4 us

        Para 10 ms:

        10000 us / 4 us = 2500 cuentas

        OCR0A = 2499
    */
	// Valor de comparación
	OCR1A = 2499;

	// Habilitar interrupción
	TIMSK1 |= (1<<OCIE1A);

	// Habilitar interrupciones globales
	sei();
}


ISR(TIMER1_COMPA_vect)
{
	ticks10ms++;		//cada 10 ms
}