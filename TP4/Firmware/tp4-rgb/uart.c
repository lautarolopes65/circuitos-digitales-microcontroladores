#include "uart.h"

static volatile char rxBuffer[RX_SIZE];
static volatile char txBuffer[TX_SIZE];
volatile uint8_t rxIndex=0;
volatile uint8_t commandReady=0;
volatile uint8_t txWrite=0;
volatile uint8_t txRead=0;


void UART_Init(void){
	
	// habilitar RX TX e interrupción RX
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0)  ;
	// 8 bits, 1 stop
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	// BaudRate=16Mhz/(UBRR+1)16 con BaudRate=9600 -> UBRR=103
	UBRR0=103;
}


void UART_SendChar(char c)
{
	uint8_t next;
	
	next = (txWrite+1)%TX_SIZE;
	while(next == txRead);
	txBuffer[txWrite]=c;
	txWrite=next;
	UCSR0B |= (1<<UDRIE0);
}


void UART_SendString(char *str)
{
	while(*str)
	{
		UART_SendChar(*str++);
	}
}

uint8_t UART_CommandReady(void)
{
	return commandReady;
}

char* UART_GetCommand(void)
{
	commandReady=0;
	return (char*)rxBuffer;
}

ISR(USART_UDRE_vect)
{
	if(txRead != txWrite)
	{
		UDR0 = txBuffer[txRead];
		txRead=(txRead+1)%TX_SIZE;
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);
	}
}

ISR(USART_RX_vect)
{
	char c;
	c=UDR0;
	
	// Final de comando
	if(c=='\r' || c=='\n')
	{
		rxBuffer[rxIndex]=0;
		commandReady=1;
		rxIndex=0;
	}
	else
	{
		if(rxIndex < RX_SIZE-1)
		{
			rxBuffer[rxIndex++]=c;
		}
	}
}