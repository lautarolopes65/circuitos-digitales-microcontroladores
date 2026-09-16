#ifndef RTC_H_
#define RTC_H_
#include <stdint.h> 

typedef struct
{
	uint8_t hora;
	uint8_t minuto;
	uint8_t segundo;
}Hora;

uint8_t BCDtoDEC(uint8_t x);
uint8_t DECtoBCD(uint8_t x);
void RTC_Init();
void RTC_Read(Hora *h);
void RTC_Set(Hora h);
uint8_t ds3231_isDaytime(Hora h);

#endif