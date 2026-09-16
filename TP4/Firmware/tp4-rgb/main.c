#include "main.h"

uint16_t adc_value,periodoT;
static uint16_t contADC=0;

int main(void)
{
	LED_Init();
	UART_Init();
	PWM_Init();
	TIMER1_Init();
	TIMER2_Init();
	ADC_Init();
	FADE_Init();
	sei();

    while (1) 
    {
		// Si se ingresa comando
		if(UART_CommandReady()){
			TERMINAL_Update();
		}
		
		/* Actualizar efecto fade y periodo cada 1 ms
			Ademas se va modificando el brillo para el efecto de desvanecimiento(fade)
		*/
		if(flag1ms){
			flag1ms = 0;
			FADE_Update();
			
			// Obtener valor de ADC(cada 100 ms) y calcular periodo T de parpadeo
			contADC++;
			if(contADC>=100){
				contADC=0;
				adc_value = ADC_Read();
				periodoT = 6000 - ((uint32_t)adc_value*3000)/1023;
				
				// Actualizar periodo T
				FADE_SetPeriodo(periodoT);
			}

			
		}
		
    }
}

