#include "mef.h"
#include "timer.h"
static eHornoState estado;
static uint16_t tiempo_seg = 0;
// Buffer MM:SS
static uint8_t digitos[4] = {0,0,0,0};
static uint8_t puertaAbierta = 0;
static uint16_t timerTicks = 0;	
static uint16_t parpadeoTicks = 0;
static uint16_t finalizadoTicks = 0;
static uint8_t parpadeo = 0;
//static uint32_t segundoAnteriorTick = 0;

// Actualiza LCD mostrando MM:SS
static void LCD_MostrarTiempo(void)
{
	char buffer[5];

	uint8_t min = tiempo_seg / 60;
	uint8_t seg = tiempo_seg % 60;

	sprintf(buffer,"%02d:%02d",min,seg);

	
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)buffer,5);
}	

// Actualiza tiempo en segundos ej: 0,1,3,0 --> min=1 y seg=30
static void actualizarTiempo(void)
{
	uint8_t min;
	uint8_t seg;

	min = digitos[0]*10 + digitos[1];
	seg = digitos[2]*10 + digitos[3];

	
	if(seg > 59)
		seg = 59;

	tiempo_seg = min*60 + seg;
}

// Desplazamiento de digitos
static void ingresarDigito(uint8_t numero)
{
	digitos[0] = digitos[1];
	digitos[1] = digitos[2];
	digitos[2] = digitos[3];
	digitos[3] = numero;

	actualizarTiempo();
}

static void resetTiempo(void)
{
	tiempo_seg = 0;
	digitos[0] = 0;
	digitos[1] = 0;
	digitos[2] = 0;
	digitos[3] = 0;
	LCDclr();
}
	
void MEF_Init()
{
	estado = INICIAL;
}


void MEF_Update()
{
		uint8_t tecla;
		int num;
		
		// LECTURA TECLADO //

		if(KEYPAD_Scan(&tecla))
		{
			convertKey(&tecla);
			
			// TECLAS NUMÉRICAS
			if(tecla >= '0' && tecla <= '9')
			{
				if(estado == INICIAL || estado == PAUSA)
				{
					num = tecla - 48;	//ascii a int
					ingresarDigito(num);
				}
			}

			// START
			if(tecla == 'A')
			{
				if(tiempo_seg > 0)
				{
					estado = COCINANDO;
				}
			}

			// STOP / CLEAR
			if(tecla == 'B')
			{
				switch(estado)
				{
					case INICIAL:
					
						resetTiempo();
						break;
						
					case COCINANDO:
					
						estado = PAUSA;
						break;
						
					case PAUSA:

						resetTiempo();
						estado = INICIAL;
						break;

					default:
						break;
				}
			}

			// +30 SEG

			if(tecla == 'C')
			{
				tiempo_seg += EXTRA_TIME;

				if((tiempo_seg) > 5999)
					tiempo_seg = 5999;

				// inicio rapido
				if(estado == INICIAL)
					estado = COCINANDO;
			}

			// PUERTA

			if(tecla == 'D')
			{
				puertaAbierta ^= 1;	//toggle 0<->1

				if(puertaAbierta)
				{
					if(estado == COCINANDO|| estado == INICIAL)
						estado = PUERTA_ABIERTA;
				}
				else
				{
					estado = INICIAL;
				}
			}
		}

	switch (estado)
	{
		case INICIAL:
		
			// Magnetron OFF
			PORTB &= ~(1<<PORTB5);
			
			// Luz OFF
			PORTC &= ~(1<<PORTC4);
			
			// Alarma OFF
			PORTC &= ~(1<<PORTC5);
			
			LCD_MostrarTiempo();
			
		break;
		
		case COCINANDO:
		
			// Magnetron ON
			PORTB |= (1<<PORTB5);
			// Luz ON
			PORTC |= (1<<PORTC4);
				
			timerTicks++;	
			if (timerTicks >= 1000) //1 seg
			{
				//segundoAnteriorTick = timerTicks;
				timerTicks = 0;
				// descontar tiempo
				if(tiempo_seg > 0)
					tiempo_seg--;

				LCD_MostrarTiempo();

				if(tiempo_seg == 0)
					estado = FINALIZADO;
			}
	
		break;

		case PAUSA:
		
			// Magnetron OFF
			PORTB &= ~(1<<PORTB5);
		
			LCDGotoXY(0,1);
			LCDstring((uint8_t*)"PAUSA",5);
			
		break;

		case FINALIZADO:

			// Magnetron OFF
			PORTB &= ~(1<<PORTB5);
			
			// Luz OFF
			PORTC &= ~(1<<PORTC4);
			
			// Alarma ON
			PORTC |= (1<<PORTC5);
			
			finalizadoTicks++;
			parpadeoTicks++;
			
			// Parpadeo cada 500ms
			if(parpadeoTicks >= 500)
			{
				parpadeoTicks = 0;

				parpadeo ^= 1; //toggle 0<->1

				if(parpadeo)
				{
					LCDblank();
					// Alarma ON
					PORTC |= (1<<PORTC5);
				}
				else
				{
					LCDvisible();
					// Alarma OFF
					PORTC &= ~(1<<PORTC5);
				}
			}
			
			if(finalizadoTicks >= 5000) //5 seg
			{
				 finalizadoTicks = 0;
				 LCDvisible();
				 resetTiempo();
				estado = INICIAL;
			}
		break;

		case PUERTA_ABIERTA:
		
			// Magnetron OFF
			PORTB &= ~(1<<PORTB5);
			
			LCDGotoXY(0,1);
			LCDstring((uint8_t*)"PUERTA ABIERTA",14);
		break;
	}
}