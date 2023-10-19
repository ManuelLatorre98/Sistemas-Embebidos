#include <xinu.h>
#include "serial.h"
#include "globals.h"
#define TICKS_UNTIL_1ms 182
int main_stick(void)
{
  int analog_in_x;
  int analog_in_y;
  int last_input_x=analog_in_x;
  int last_input_y=analog_in_y;
  serial_put_str("\rStick start\r\n");
  while(1){
    analog_in_x=adc_get(0); //Valores de 0 a 1023 !Este llega a 1020
    analog_in_y=adc_get(1); //Valores de 0 a 1023 

    //Centered stick: (511, 495)

    if(analog_in_x > last_input_x+2 || analog_in_x < last_input_x-2 || analog_in_y > last_input_y+2 || analog_in_y < last_input_y-2){
      last_input_x=analog_in_x;
      last_input_y=analog_in_y;
      set_mov_base(analog_in_x, analog_in_y);
    }

    /* 
     Cuando se detecten variaciones en x o y llamar a metodo que detecte index y direction
     de ahi se llama a justar serv angle
     */
  } 
}

//SERVOS 0,1
int set_mov_base(int analog_in_x, int analog_in_y){
  	volatile int servo_index=-1;
	  volatile int direction=-1; //-1 = error, 0 = left, 1 = right
    if(analog_in_x>515){
      servo_index=0;
      direction=0;
    
    }else if(analog_in_x<504){
      servo_index=0;
      direction=1;
    
    }
    if(analog_in_y>500){
      servo_index=1;
      direction=0;
    }else if(analog_in_y<490){
      servo_index=1;
      direction=1;
    }
  

    if(servo_index>-1 && direction>-1){
      adjust_servo_angle(servo_index, direction);
    }
    
}

void adjust_servo_angle(int servo_index, int direction)
{
	if(servo_index>-1){
		if (direction==0 && servo_angles[servo_index] > 0)
		{
			servo_angles[servo_index] -= 20;
			servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
			print_array();
		}else if (direction==1 && servo_angles[servo_index] < 100) //!Con rango [0,100] llega a 2ms
		{
			servo_angles[servo_index] += 20;
			servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
			print_array();
		}
	}
}

void print_array()
{
/*   serial_put_str_inline("[");
	for(int i = 0; i<N_SERVOS; i++){
		serial_put_int(servo_angles[i],3);
    serial_put_str_inline(", ");
	}
  serial_put_str_inline("] "); */

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


