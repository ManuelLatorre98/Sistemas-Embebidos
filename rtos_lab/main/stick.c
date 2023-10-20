#include <xinu.h>
#include "serial.h"
#include "globals.h"
#define TICKS_UNTIL_1ms 182
#define ANGLE_STEP 5
//Valores analogicos del stick. Defino la sensibilidad para evitar ajustes cuando se vuelve a centrar
#define CENTERED_X 511
#define CENTERED_Y 495
#define SENS_X 30
#define SENS_Y 30
int apretado=0;
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


    /* if(analog_in_x > last_input_x+2 || analog_in_x < last_input_x-2 || analog_in_y > last_input_y+2 || analog_in_y < last_input_y-2){
      last_input_x=analog_in_x;
      serial_put_int(analog_in_x, 4);
    } */
    if(analog_in_x > last_input_x+2 || analog_in_x < last_input_x-2 || analog_in_y > last_input_y+2 || analog_in_y < last_input_y-2){
      last_input_x=analog_in_x;
      last_input_y=analog_in_y;
      set_mov_base(analog_in_x, analog_in_y);
    }
    stick_click();
    /* 
     Cuando se detecten variaciones en x o y llamar a metodo que detecte index y direction
     de ahi se llama a justar serv angle
     */
   
  } 
}

//SERVOS 0,1
int set_mov_base(int analog_in_x, int analog_in_y){
  	volatile int servo_index_x=-1;
	  volatile int direction_x=-1; //-1 = error, 0 = left, 1 = right

    volatile int servo_index_y=-1;
	  volatile int direction_y=-1; //-1 = error, 0 = left, 1 = right
    //Control eje x
    if(analog_in_x > (CENTERED_X + SENS_X)){
      servo_index_x=0;
      direction_x=0;
    
    }else if(analog_in_x < (CENTERED_X - SENS_X)){
      servo_index_x=0;
      direction_x=1;
    }

    if(servo_index_x > -1 && direction_x > -1){
      adjust_servo_angle(servo_index_x, direction_x);
    }

    //Control eje y
    if(analog_in_y > (CENTERED_Y + SENS_Y)){
      servo_index_y=1;
      direction_y=0;
    }else if(analog_in_y < (CENTERED_Y - SENS_Y)){
      servo_index_y=1;
      direction_y=1;
    }

    if(servo_index_y>-1 && direction_y>-1){
      adjust_servo_angle(servo_index_y, direction_y);
    }
    
}

void adjust_servo_angle(int servo_index, int direction)
{
	if(servo_index>-1){
		if (direction==0 && servo_angles[servo_index] > 0)
		{
			servo_angles[servo_index] -= ANGLE_STEP;
			servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
			print_array();
		}else if (direction==1 && servo_angles[servo_index] < 100) //!Con rango [0,100] llega a 2ms
		{
			servo_angles[servo_index] += ANGLE_STEP;
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

void stick_click(){
  int bitIn = *(PIN_B) & 0b00010000;
  volatile long i=0;
  int bitEncendido= *(PUERTO_B) & 0b00100000;//Obtengo estado
    
  if(bitIn==0 && apretado==0){//Si apretó y no venia pulsando 
    for(i=0; i<1000; i++){} 
    if(bitEncendido==0){//Si estaba apagado lo prende
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
    }else{//Si estaba prendido lo apaga
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
    }
    apretado=1;
  }

  if(bitIn!=0 && apretado==1){ //Si deje de pulsar y venia pulsando
    *(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
    for(i=0; i<1000; i++){} 
    apretado=0;
  }
}


