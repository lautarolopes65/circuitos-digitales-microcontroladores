#include <avr/io.h>
#include "i2c.h"

#define F_CPU 16000000UL

/* REGISTROS I2C/TWI

TWCR: |TWINT|TWEA|TWSTA|TWSTO|TWWC|TWEN|-|TWIE|

• TWINT: TWI Interrupt flag
• TWEA: TWI Enable Acknowledge bit
	• 1:ACK, 0:NACK
• TWSTA: TWI Start condition bit
• TWSTO: TWI Stop condition bit
• TWWC: TWI Write Collision flag
• TWEN: TWI Enable bit
• TWIE: TWI Interrupt Enable
*/

void I2C_Init(void)
{
	TWSR=0;

	//fSCL=100kHz
	TWBR=((F_CPU/100000)-16)/2;
	TWCR=(1<<TWEN);
}



uint8_t I2C_Start(uint8_t address)
{

	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	TWDR=address;

	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	// Lee el codigo de estado TWI y chequea respuesta del esclavo. 
	if((TWSR & 0xF8)!=TWI_MT_SLA_ACK && (TWSR & 0xF8)!=TWI_MR_SLA_ACK)
	{
		return 0;
	}

	return 1;
}



void I2C_Stop()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}



uint8_t I2C_Write(uint8_t data)
{

	TWDR=data;

	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	return 1;

}



uint8_t I2C_Read_ACK()
{

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

	while(!(TWCR&(1<<TWINT)));

	return TWDR;

}



uint8_t I2C_Read_NACK()
{

	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	return TWDR;

}