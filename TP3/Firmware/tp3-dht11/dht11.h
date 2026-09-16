#ifndef DHT11_H_
#define DHT11_H_

#define DHT_PIN PC0
#define TIMEOUT 500

uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum);

#endif