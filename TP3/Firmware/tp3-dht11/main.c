#include "main.h"
#include "rtc.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
  UART_Init();
  RTC_Init();
  TIMER_Init();
  
  sei();

  while(1)
  {
	  TERMINAL_Update();
	  
  }
}

