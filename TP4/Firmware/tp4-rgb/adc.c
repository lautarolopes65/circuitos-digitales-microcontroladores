#include "adc.h"

void ADC_Init(void){
	// Configurar PC3 como entrada analógica(ADC3)
	DDRC &= ~(1<<PORTC3);
	DIDR0 |= (1<<ADC3D);
	
	// Habilitar ADC
	ADCSRA |= (1<<ADEN);
	
	// Establecer Vref=VCC como referencia
	ADMUX |= (1<<REFS0);
	
	// Seleccionar canal ADC3
	ADMUX |= (1<<MUX1)|(1<<MUX0);
		
	// Prescaler de 128, asi 16 MHz/128 = 125kH (<200 Hz)
	// Se garantiza mejor performance hasta 200 kHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	

}

uint16_t ADC_Read(void){
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	
	// Esperar que termine
	while(ADCSRA & (1<<ADSC));
	
	return ADC;
}