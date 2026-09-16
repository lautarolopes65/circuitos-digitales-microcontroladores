#ifndef TECLADO4X4_H
#define TECLADO4X4_H

#include <avr/io.h>

void KEYPAD_Init(void);
uint8_t KEYPAD_Update(void);
uint8_t KEYPAD_Scan (uint8_t *pkey);
void convertKey(uint8_t *key);

#endif