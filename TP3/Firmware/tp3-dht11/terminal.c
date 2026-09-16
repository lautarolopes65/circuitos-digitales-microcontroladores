#include <stdio.h>
#include <string.h>

#include "terminal.h"
// Periodo de reporte en segundos
 uint16_t periodoReporte=5;
 uint32_t ultimoReporte=0;
// Buffer donde se arma el comando
static char comando[BUFFER_CMD];
uint8_t contadorAlertas=0;
extern volatile uint32_t ticks10ms;

/*
  TERMINAL_Update() 
  Esta funcion verifica:
 
   Si llega un comando por UART:
       - Procesa el comando inmediatamente.
 
   Si se cumple el tiempo de muestreo:
       - Lee RTC.
       - Lee DHT11.
       - Envía la trama por UART.
	   
	ticks10ms aumenta cada 10 ms.
	periodoReporte está expresado en segundos.
		
		--> 1 segundo = 100 ticks de 10 ms
		
	se multiplica periodoReporte por 100 para convertir segundos a unidades del contador del Timer.
		
	Ejemplo: periodoReporte = 5 segundos
		
	Entonces:
		5 * 100 = 500 ticks
		
	Cuando ticks10ms - ultimoReporte >= 500
	significa que transcurrieron 5 segundos desde el último reporte.
		
	Luego se actualiza:
		
		ultimoReporte = ticks10ms
		
	reiniciando la medicion del proximo intervalo
 */

void TERMINAL_Update()
{    
	if(UART_CommandReady())
	{
		TERMINAL_ProcessCommand();
		return;
	}
	
	if((ticks10ms - ultimoReporte) >= periodoReporte*100)
	{
		ultimoReporte = ticks10ms;
		TERMINAL_SendReporte();
	}
	
}

//------------------------------------
// Genera la trama de reporte
//------------------------------------

void TERMINAL_SendReporte(void)
{
	Hora h;
	uint8_t temp,hum, alerta=0;

	char buffer[80],motivo[40];

	RTC_Read(&h);

	DHT11_Read(&temp,&hum);

	if(h.hora>=7 && h.hora<19)
	{
		if(temp>=20 && temp<=30 && hum>=50 && hum<=70)
		{
			sprintf(buffer,
			"[%02d:%02d:%02d] T:%02dC | H:%02d%% | Estado:NORMAL\r\n",
			h.hora,h.minuto,h.segundo,temp,hum);
		}
		else //ALERTA diurna
		{
			alerta=1;
			if(temp<20 && temp>30){
				sprintf(motivo,
				"Temperatura fuera de rango diurno! Valor:%02dC",temp);
			}
			else
			{
				sprintf(motivo,
				"Humedad fuera de rango diurno! Valor:%02d%%",hum);
			}
			sprintf(buffer,
			"[%02d:%02d:%02d] T:%02dC | H:%02d%% | Estado:ALERTA\r\n",
			h.hora,h.minuto,h.segundo,temp,hum);
		}
	}
	else
	{
		if(temp>=15 && temp<=22 && hum>=60 && hum<=80)
		{
			sprintf(buffer,
			"[%02d:%02d:%02d] T:%02dC | H:%02d%% | Estado:NORMAL\r\n",
			h.hora,h.minuto,h.segundo,temp,hum);
		}
		else//ALERTA nocturna
		{
			alerta=1;
			if(temp<15 && temp>22){
				sprintf(motivo,
				"Temperatura fuera de rango nocturno! Valor:%02dC",temp);
			}
			else
			{
				sprintf(motivo,
				"Humedad fuera de rango nocturno! Valor:%02d%%",hum);
			}
			sprintf(buffer,
			"[%02d:%02d:%02d] T:%02dC | H:%02d%% | Estado:ALERTA\r\n",
			h.hora,h.minuto,h.segundo,temp,hum);
		}
	}
	
	UART_SendString(buffer);
	
	if(alerta)
	{
		contadorAlertas++;

	if(contadorAlertas>=2)
	{
		contadorAlertas=0;

		sprintf(buffer,
		"[ALERTA] [%02d:%02d:%02d] %s\r\n",
		h.hora,
		h.minuto,
		h.segundo,
		motivo);


		UART_SendString(buffer);
	}
}
else
{
	contadorAlertas=0;
}
}


//------------------------------------
// Lee el buffer de UART y procesa
//------------------------------------

void TERMINAL_ProcessCommand(void)
{

	if(!UART_CommandReady())
		return;

	strcpy(comando,UART_GetCommand());

	// SET_TIME=HH:MM:SS
	if(strncmp(comando,"SET_TIME=",9)==0)
	{
		Hora h;

		sscanf(&comando[9],"%hhu:%hhu:%hhu",&h.hora,&h.minuto,&h.segundo);
		RTC_Set(h);
		UART_SendString("Hora actualizada\r\n");
	}

	// SET_TM=SS

	else if(strncmp(comando,"SET_TM=",7)==0)
	{
		uint8_t nuevo;

		sscanf(&comando[7],"%hhu",&nuevo);
		if(nuevo>=2 && nuevo<=60)
		{
			periodoReporte=nuevo;

			UART_SendString("Periodo actualizado\r\n");
		}
		else
		{
			UART_SendString("Periodo invalido\r\n");
		}
	}
	else
	{
		UART_SendString("Comando invalido\r\n");
	}


}