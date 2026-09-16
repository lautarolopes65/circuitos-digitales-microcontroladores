#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <avr/interrupt.h>

/* Como maximo "SET_COLOR=RRR,GGG,BBB" */
#define RX_SIZE 25
/* Como maximo "Color Actualizado"	   */
#define TX_SIZE 22

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *s);
uint8_t UART_CommandReady(void);
char* UART_GetCommand(void);


#endif