#include "pwm.h"

static volatile uint8_t pwm_pos=0;
static volatile uint8_t pwm_dutyRed=0;

/*
	Configuracion de los PWM
	
	Señal R --> PB5 por SOFTWARE
	Señal G --> PB2 por HARDWARE(Timer1)
	Señal B --> PB1 por HARDWARE(Timer1)
*/
void PWM_Init(void){
	DDRB|= (1<<PB5); // R
	DDRB|=(1<<PB2);	 // G
	DDRB|=(1<<PB1);	 // B
	
    // Timer0 Modo CTC, prescaler 8, OCR0A=129 para f = 60.01 Hz

    TCCR0A = (1 << WGM01); 
    TCCR0B = (1 << CS01);  
    OCR0A = 129;
	
	// Habilitar interrupción por comparación
    TIMSK0 = (1 << OCIE0A);   	
}

void PWM_Set(uint8_t r,uint8_t g,uint8_t b)
{
	pwm_dutyRed=r;
	OCR1A=255-b;	
	OCR1B=255-g;	
}

ISR(TIMER0_COMPA_vect){
	if(++pwm_pos > TOP)
		pwm_pos = 0;
		
	if (pwm_pos < pwm_dutyRed)
		PORTB &= ~(1<<PORTB5);
	else 
		PORTB |= (1<<PORTB5);
	
}