#include "teclado4x4.h"

#define F_CPU 16000000UL
#include <util/delay.h>

/*
    Salidas del micro (filas):
    A -> PB4
    B -> PB3
    C -> PB0
    D -> PD7
    Entradas del micro (columnas):
    1 -> PD3
    2 -> PD5
    3 -> PD4
    4 -> PD2
*/

void KEYPAD_Init(void)
{
	// Filas -> salidas
	DDRB |= (1<<PORTB0) | (1<<PORTB3) | (1<<PORTB4);
	DDRD |= (1<<PORTD7);

	// Columnas -> entradas
	DDRD &= ~((1<<PORTD3) | (1<<PORTD5) |
	(1<<PORTD4) | (1<<PORTD2));

	// Pull-up
	PORTD |= (1<<PORTD3) | (1<<PORTD5) |
	(1<<PORTD4) | (1<<PORTD2);

	// Filas inicialmente en alto
	PORTB |= (1<<PORTB0) | (1<<PORTB3) | (1<<PORTB4);
	PORTD |= (1<<PORTD7);
}

uint8_t KEYPAD_Update(void)
{
	uint8_t pinsFilas[] = {PB4, PB3, PB0, PD7};
	uint8_t pinsColumnas[] = {PD3, PD5, PD4, PD2};

	uint8_t r,c;

	for(r=0;r<4;r++)
	{
		// Pongo TODAS las filas en alto
		PORTB |= (1<<PORTB0) | (1<<PORTB3) | (1<<PORTB4);
		PORTD |= (1<<PORTD7);

		// Bajo una fila
		if(r==3)
		PORTD &= ~(1<<pinsFilas[r]);
		else
		PORTB &= ~(1<<pinsFilas[r]);

		_delay_us(10);

		// Leo columnas
		for(c=0;c<4;c++)
		{
			if(!(PIND & (1<<pinsColumnas[c])))
			{
				return (r*4+c);
			}
		}
	}

	return 0xFF; //tecla no presionada
}

uint8_t KEYPAD_Scan (uint8_t *pkey)
{
	static uint8_t Old_key, Last_valid_key=0xFF; // no hay tecla presionada;
	uint8_t Key;
	
	Key= KEYPAD_Update();
	if(Key==0xFF){
		Old_key=0xFF; // no hay tecla presionada
		Last_valid_key=0xFF;
		return 0;
	}
	if(Key==Old_key) { //2da verificación
		if(Key!=Last_valid_key){ //evita múltiple detección
			*pkey=Key;
			Last_valid_key = Key;
			return 1;
		}
	}
	Old_key=Key; //1era verificación
	return 0;
}

void convertKey(uint8_t *key) 
{
	switch(*key)
	{
		case 0: *key='1'; break;
		case 1: *key='2'; break;
		case 2: *key='3'; break;
		case 3: *key='A'; break;

		case 4: *key='4'; break;
		case 5: *key='5'; break;
		case 6: *key='6'; break;
		case 7: *key='B'; break;

		case 8: *key='7'; break;
		case 9: *key='8'; break;
		case 10:*key='9'; break;
		case 11:*key='C'; break;

		case 12:*key='*'; break;
		case 13:*key='0'; break;
		case 14:*key='#'; break;
		case 15:*key='D'; break;
	}
 }