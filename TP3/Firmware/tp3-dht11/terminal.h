#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <stdint.h>
#include "uart.h"
#include "rtc.h"
#include "timer.h"
#include "dht11.h"
#define BUFFER_CMD 32

void TERMINAL_Update(void);
//void TERMINAL_SendReporte(Hora h,uint8_t temp,uint8_t hum,uint8_t estado);
void TERMINAL_SendReporte(void);
//void TERMINAL_ProcessCommand(char *cmd);
void TERMINAL_ProcessCommand(void);

#endif