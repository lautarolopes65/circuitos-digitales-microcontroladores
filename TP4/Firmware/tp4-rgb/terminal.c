#include "terminal.h"

#include <stdio.h>
#include <string.h>

// Buffer donde se arma el comando
static char comando[BUFFER_CMD];

void TERMINAL_Update()
{    
	if(UART_CommandReady())
	{
		TERMINAL_ProcessCommand();
		return;
	}
	
}

// Leer el buffer de UART y procesar

void TERMINAL_ProcessCommand(void)
{
	// Obtener comando
	strcpy(comando,UART_GetCommand());
	
	// Chequear estructura -> SET_COLOR=rrr,ggg,bbb 
 	if(strncmp(comando,"SET_COLOR=",10)==0)
 	{
		uint8_t r,g,b;

		sscanf(&comando[10],"%hhu,%hhu,%hhu",&r,&g,&b);

		LED_SetRGB(r,g,b);
		UART_SendString("Color Actualizado\r\n");

	}

	// INVALIDO
	else
	{
		//UART_SendString("Comando invalido\r\n");
	}


}