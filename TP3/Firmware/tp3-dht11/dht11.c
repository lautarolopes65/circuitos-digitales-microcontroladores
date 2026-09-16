#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "dht11.h"


// Espera hasta que el pin llegue al estado esperado
// estado = 0 espera LOW
// estado = 1 espera HIGH
static uint8_t esperarEstado(uint8_t estado)
{
	uint16_t contador=0;

	if(estado)
	{
		// Esperar HIGH
		while(!(PINC & (1<<DHT_PIN)))
		{
			_delay_us(1);
			contador++;
			if(contador > TIMEOUT)
				return 0;
		}
	}
	else
	{
		// Esperar LOW
		while(PINC & (1<<DHT_PIN))
		{
			_delay_us(1);
			contador++;
			if(contador > TIMEOUT)
				return 0;
		}
	}
	return 1;
}

/* Implementacion para lectura: 
	1. MCU envia LOW al sensor por PC0 durante 18ms (start signal) 
	2. MCU libera PC0 (pull-up externo de 10k la lleva a HIGH) 
	3. DHT11 responde despues de 20-40 us 
	4. DHT11 responde: LOW ~80us, luego HIGH ~80us 
	5. DHT11 transmite 40 bits (5 bytes): 
	[0] Humedad entera [1] Humedad decimal 
	[2] Temp entera [3] Temp decimal 
	[4] Checksum = suma de bytes 0..3 
	Antes de cada bit -> LOW ~50 us luego: 
		- bit 0: HIGH 26-28 us 
		- bit 1: HIGH ~70us 
*/
/*
  La funcion DHT11_Read devuelve:
  
  1 -> lectura correcta
  Los valores de temperatura y humedad son válidos.
  
  0 -> lectura incorrecta
	 Por:
		- sensor desconectado
		- falta de respuesta del DHT11
		- checksum inválido
  
  Si devuelve 0, el sistema no utiliza los datos obtenidos y envía un mensaje de error por UART.
 */
uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum)
{
	uint8_t data[5]={0};

	uint8_t byteData;
	uint8_t bitData;

	/*
		START:
		MCU pone la linea en LOW
	*/

	DDRC |= (1<<DHT_PIN);
	PORTC &= ~(1<<DHT_PIN);

	_delay_ms(18);

	/*
		Liberar linea:
		La resistencia de 10k la lleva a HIGH
	*/

	DDRC &= ~(1<<DHT_PIN);
	PORTC &= ~(1<<DHT_PIN);

	/*
		Respuesta DHT11:
		LOW 80us
		HIGH 80us
	*/

	if(!esperarEstado(0))
		return 0;

	if(!esperarEstado(1))
		return 0;

	if(!esperarEstado(0))
		return 0;


	/*
		Leer 40 bits
		Cada bit:
		LOW 50us
		HIGH:
		  26us -> 0
		  70us -> 1

	*/

	for(byteData=0; byteData<5; byteData++)
	{

		for(bitData=0; bitData<8; bitData++)
		{
			// Espero comienzo del bit
			if(!esperarEstado(1))
				return 0;
				
			// Muestreo
			_delay_us(30);

			data[byteData]<<=1;


			if(PINC & (1<<DHT_PIN))
			{
				data[byteData]|=1;
			}

			// espero que termine el bit
			if(!esperarEstado(0))
				return 0;

		}

	}

	//	Checksum
	if((data[0]+data[1]+data[2]+data[3]) != data[4])
	{
		return 0;
	}

	//	Datos validos
	*hum=data[0];
	*temp=data[2];
	return 1;

}
