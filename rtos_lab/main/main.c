#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
#include <avr/interrupt.h>
/* definicion de tareas (cuyo codigo fuente es externo) */
#define TICKS_UNTIL_1ms 182

int main(void)
{
	char rcv_char = ' ';
	serial_init();
	
	*(DDR_B) |= 0b00101111; // bit 5= led arduino, pb0,1,2,3,4 = salidas de servos
	*(PUERTO_B) |= 0b00101111;//Arranca con las señales todas en alto. El led encendido
	//sleep(5);
	//timer1_init();
	
	/* creamos y ponemos a ejecutar las tareas */
/* 	resume(create(main_rtc, 60, 30, "rtc", 0));
	resume(create(main_show_data, 60, 30, "sho", 0)); */

	serial_put_str("\rRTOS_LAB INICIADO\r\n");
/* 	sei(); */
	print_array();
	volatile int servo_index=-1;
	volatile int direction=-1; //-1 = error, 0 = left, 1 = right
	while (1)
	{
		if (serial_getchar_ready())
		{
			rcv_char = serial_get_char();
			switch (rcv_char)
			{
				//SERVO 0
				case 'q':
					servo_index=0;
					direction=0;
					break;
				case 'e':
					servo_index=0;
					direction=1;
					break;
				//SERVO 1
				case 'a':
					servo_index=1;
					direction=0;
					break;
				case 'd':
					servo_index=1;
					direction=1;
					break;
				//SERVO 2
				case 'z':	
					servo_index=2;
					direction=0;
					break;
				case 'c':
					servo_index=2;
					direction=1;
					break;
				//SERVO 3
				case 'r':	
					servo_index=3;
					direction=0;
					break;
				case 'y':
					servo_index=3;
					direction=1;
					break;
				//SERVO 4
				case 'f':	
					servo_index=4;
					direction=0;
					break;
				case 'h':
					servo_index=4;
					direction=1;
					break;
				default:
					servo_index=-1;
					direction=-1;
					break;
			}
			//serial_put_int(servo_index);
			adjust_servo_angle(rcv_char,servo_index, direction);
			//Resetea variables para la siguiente iteracion
			if(servo_index>-1 || direction>-1){
				servo_index=-1;
				direction=-1;
			}
			
			/* if (rcv_char == 'a' || rcv_char == 'd')
			{
				adjust_servo_angle(rcv_char,0); //todo luego agregar la referencia al servo como param
			} */
		} 
		
		//sleepms(30); //!ver porque no funciona el sleepms
	
	
	}
	return 0;
}

void adjust_servo_angle(char rcv_char, int servo_index, int direction)
{
	if(servo_index>-1){

		if (direction==0 && servo_angles[servo_index] > 0)
		{
			servo_angles[servo_index] -= 20;
			servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
			print_array();
		}else if (direction==1 && servo_angles[servo_index] < 180)
		{
			servo_angles[servo_index] += 20;
			servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
			print_array();
		}

	}
}

void print_array()
{
  serial_put_str_inline("[");
	for(int i = 0; i<N_SERVOS; i++){
		serial_put_int(servo_angles[i],3);
    serial_put_str_inline(", ");
	}
  serial_put_str_inline("] ");

	serial_put_str_inline("[");
	for(int i = 0; i<N_SERVOS; i++){
		serial_put_int(servo_ticks[i],3);
    serial_put_str_inline(", ");
	}
  serial_put_str_inline("] ");
	
}

int getTicksOffset(int angle)
{
  int result= TICKS_UNTIL_1ms + angle;
	return result;
}