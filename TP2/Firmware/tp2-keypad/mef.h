#ifndef MEF_H_
#define MEF_H_

#include <stdio.h>
#include "lcd.h"
#include "teclado4x4.h"
#include "timer.h"
typedef enum {INICIAL,COCINANDO,PAUSA,FINALIZADO,PUERTA_ABIERTA} eHornoState;

#define EXTRA_TIME 30

void MEF_Init();
void MEF_Update();

#endif 