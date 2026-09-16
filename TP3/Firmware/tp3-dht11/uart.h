#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include <avr/interrupt.h>

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *s);
uint8_t UART_CommandReady(void);
char* UART_GetCommand(void);

#endif