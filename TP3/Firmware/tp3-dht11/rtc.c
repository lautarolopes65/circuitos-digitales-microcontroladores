#include "rtc.h"
#include "i2c.h"

#define RTC_ADDR 0x68 // Direccion I2C fija del DS3232  

uint8_t BCDtoDEC(uint8_t x)
{
	return ((x>>4)*10)+(x&0x0F);
}


uint8_t DECtoBCD(uint8_t x)
{
	return ((x/10)<<4)|(x%10);
}

void RTC_Init()
{
	I2C_Init();
}

void RTC_Read(Hora *h)
{

	I2C_Start(RTC_ADDR<<1);
	I2C_Write(0x00);
	I2C_Start((RTC_ADDR<<1)|1);
	
	h->segundo = BCDtoDEC(I2C_Read_ACK());
	h->minuto = BCDtoDEC(I2C_Read_ACK());
	h->hora = BCDtoDEC(I2C_Read_NACK());
	
	I2C_Stop();
}

void RTC_Set(Hora h)
{
// Escritura: START -> addr + W -> reg_base -> seg -> min -> horas -> STOP 
	I2C_Start(RTC_ADDR<<1);
	I2C_Write(0x00);

	I2C_Write(DECtoBCD(h.segundo));
	I2C_Write(DECtoBCD(h.minuto));
	I2C_Write(DECtoBCD(h.hora));

	I2C_Stop();
}
