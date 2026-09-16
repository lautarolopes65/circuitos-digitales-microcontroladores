#include "fade.h"

/*
	CONTROL DEL FADE: Implementado con una MEF con 4 estados
		
		SUBIENDO -> 1 s
		MAXIMO	 -> 1 s		
		BAJANDO	 -> 1 s 	
		APAGADO  -> T-3 s
	
	El FADE_Update() se ejecuta cada 1ms, asique todos los tiempos estan en ms.
	El nivel de brillo en las rampas(SUBIENDO Y BAJANDO) va variando mediante la formula --> brillo=tiempoEstado*255/TIEMPO_RAMPA
*/
estadoLed estado;
static uint16_t tiempoEstado = 0;;

// Brillo 0 - 255
static uint8_t brillo;

static uint16_t periodo = 6000;
static uint16_t tiempoApagado = 0;


void FADE_Init(void)
{
	estado = SUBIENDO;
	tiempoEstado = 0;
	brillo = 0;
}

void FADE_SetPeriodo(uint16_t T)
{
	if(T < LED_ON_MS)
		T = LED_ON_MS;

	periodo = T;
	
	// El tiempo encendido del led es como minimo 3 seg. --> el tiempo apagado es T-3 seg.
	tiempoApagado = periodo-LED_ON_MS;
}

void FADE_Update(void)
{
	tiempoEstado++;
	switch(estado)
	{

		case SUBIENDO:

			brillo = ((uint32_t)tiempoEstado*255)/RAMPA_MS;
			if(tiempoEstado >= RAMPA_MS){
				estado = MAXIMO;
				brillo = 255;
				tiempoEstado = 0;
			}

		break;

		case MAXIMO:
		
			brillo = 255;
			if(tiempoEstado >= MAXIMO_MS){
				estado = BAJANDO;
				tiempoEstado = 0;
			}
			
		break;

		case BAJANDO:
		
			brillo = 255 - ((uint32_t)tiempoEstado*255)/RAMPA_MS;
			if(tiempoEstado >= RAMPA_MS){
				estado = APAGADO;
				brillo = 0;
				tiempoEstado = 0;
			}

		break;

		case APAGADO:

			brillo = 0;
			if(tiempoEstado >= tiempoApagado){
				estado = SUBIENDO;
				tiempoEstado = 0;
			}

		break;
	}
	
	
    // Aplicar el brillo al LED
    LED_AplicarBrillo(brillo);

}