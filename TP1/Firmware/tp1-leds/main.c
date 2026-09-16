#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define MSB 7
#define LSB 0
#define NOP asm volatile("nop\n\t")

//---------------- VARIABLES GLOBALES ----------------//

// Estado de secuencias
uint8_t estAct1 = 0; // 0=A, 1=B
uint8_t estAct2 = 0; // 0=C, 1=D

// Contadores de tiempo (simulan 100ms y 150ms)
uint16_t cont1 = 0;
uint16_t cont2 = 0;

// Estados internos
uint8_t ledSec1 = LSB;
uint8_t subir = 1;

// Botones (estado anterior)
uint8_t ant0 = 1;
uint8_t ant1 = 1;

//---------------- CONFIGURACIÓN DE PUERTOS----------------//

void configurarPuertos(){
	DDRD = 0xFF;     // PORTD salida (LEDs)
	PORTD = 0x00;

	DDRC &= ~((1<<PINC0)|(1<<PINC1)); // entradas
	PORTC |= (1<<PINC0)|(1<<PINC1);   // pull-up

	DDRB |= (1<<PINB0); // salida neopixel
}

//---------------- SECUENCIAS EN LEDS ----------------//

void secuenciaA(){
	PORTD = (1<<ledSec1);

	// Avanza de LSB a MSB
	if(ledSec1 == MSB)
		ledSec1 = LSB;
	else
		ledSec1++;
}

void secuenciaB(){
	PORTD = (1<<ledSec1);

	// Rebote
	if(ledSec1 == MSB) subir = 0;
	if(ledSec1 == LSB) subir = 1;

	if(subir) ledSec1++;
	else ledSec1--;
}

//---------------- NEOPIXEL ----------------//

// envia byte a Neopixel
void neopixel_enviarByte(uint8_t byte){
	for(uint8_t i=0;i<8;i++){
		if(byte & 0x80){ //bit=1
			PORTB |= (1<<PINB0); // 3 ciclos --> 187.5 ns 
			NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP; // 10 NOP's ---> 625 ns
			// total = 187.5 + 625 = 812,5 ns (> 0.8 us)
			PORTB &= ~(1<<PINB0); // 3 ciclos --> 187.5 ns 
			NOP;NOP;NOP;NOP;NOP; // 6 NOP's ---> 312.5 ns
			// total = 187.5 + 312.5 = 500 ns (> 0.45 us)
		}else{ //bit=0
			PORTB |= (1<<PINB0); // 3 ciclos --> 187.5 ns 
			NOP;NOP;NOP;NOP; // 4 NOP's --> 250 ns
			// total = 187.5 + 250 = 437.5 ns (> 0.4 us)
			PORTB &= ~(1<<PINB0); // 3 ciclos --> 187.5 ns 
			NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP;NOP; // 11 NOP's --> 687.5 ns
			// total = 187.5 + 687.5 = 875 ns (> 0.85 us)
		}
		byte <<= 1;
	}
}

void neopixel_color(uint8_t r, uint8_t g, uint8_t b){
	neopixel_enviarByte(g);
	neopixel_enviarByte(r);
	neopixel_enviarByte(b);
}

//---------------- SECUENCIAS NEOPIXEL ----------------//

void secuenciaC(){
	static uint8_t fase = 0;
	fase ^= 1;

	for(uint8_t i=0;i<8;i++){
		if(i%2==0){ // pares
			if(fase) neopixel_color(255,0,0); // rojo
			else neopixel_color(0,0,0); // apagado
		}else{ // impares
			if(!fase) neopixel_color(0,0,255); // azul
			else neopixel_color(0,0,0); // apagado
		}
	}

	// Reset del WS2812 (>50us)
	for(uint16_t i=0;i<1000;i++) NOP;
}

void secuenciaD(){
	static int8_t pos = 7;

	for(uint8_t i=0;i<8;i++){
		if(i == pos) neopixel_color(0,255,0);
		else neopixel_color(0,0,0);
	}

	// Movimiento
	if(pos == 0) pos = 7;
	else pos--;

	// Reset
	for(uint16_t i=0;i<1000;i++) NOP;
}

//---------------- BOTONES ----------------//

void leerBotones(){
	uint8_t act0 = (PINC & (1<<PINC0)) ? 1 : 0;
	uint8_t act1 = (PINC & (1<<PINC1)) ? 1 : 0;

	// Flanco descendente -> botón presionado
	if(ant0 && !act0){
		estAct1 ^= 1; // cambia secuencia A/B
	}

	if(ant1 && !act1){
		estAct2 ^= 1; // cambia secuencia C/D
	}

	// Guardar estado anterior
	ant0 = act0;
	ant1 = act1;
}


int main(void){

	configurarPuertos();

	while(1){
		
		// delay 1 ms
		_delay_ms(1); 

		// Incremento de contadores
		cont1++;
		cont2++;

		// Leer botones
		leerBotones();

		// Tarea LEDs (100ms)
		if(cont1 >= 100){ 
			cont1 = 0;

			if(estAct1==0) secuenciaA();
			else secuenciaB();
		}

		// Tarea neopixel (150ms)
		if(cont2 >= 150){
			cont2 = 0;

			if(estAct2==0) secuenciaC();
			else secuenciaD();
		}

	}
}
