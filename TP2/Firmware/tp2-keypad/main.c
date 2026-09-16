#include "main.h"

int main(void)
{
	LEDS_Init();
    LCD_Init();
	KEYPAD_Init();
	TIMER_Init();
	MEF_Init();
	
    while (1) 
    {
		if (flagMEF)
		{
			flagMEF=0;
			MEF_Update();
		}
	}
}

void LEDS_Init(void){
	DDRB |= (1<<PORTB5);
	DDRC |= (1<<PORTC4) | (1<<PORTC5);
}