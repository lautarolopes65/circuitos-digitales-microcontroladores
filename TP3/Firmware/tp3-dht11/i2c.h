#ifndef I2C_H_
#define I2C_H_
#include <stdint.h> 
// Codigos de estados de TWI (TWSR & 0xF8).
#define TWI_START        0x08  // Condicion START transmitida              
#define TWI_REP_START    0x10  // Condicion START repetida transmitida     
#define TWI_MT_SLA_ACK   0x18  // Master TX: SLA+W enviado, ACK recibido
#define TWI_MT_DATA_ACK  0x28  // Master TX: dato enviado, ACK recibido  
#define TWI_MR_SLA_ACK   0x40  // Master RX: SLA+R enviado, ACK recibido 
#define TWI_MR_DATA_ACK  0x50  // Master RX: dato recibido, ACK enviado  
#define TWI_MR_DATA_NACK 0x58  // Master RX: dato recibido, NACK enviado 

void I2C_Init(void);
uint8_t I2C_Start(uint8_t address);
void I2C_Stop(void);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_Read_ACK(void);
uint8_t I2C_Read_NACK(void);

#endif