#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include <avr/interrupt.h>
#define TICKS_UNTIL_1ms 182
#define ANGLE_STEP 5
//Valores analogicos del stick. Defino la sensibilidad para evitar ajustes cuando se vuelve a centrar
#define CENTERED_X 511
#define CENTERED_Y 495
#define SENS_X 40
#define SENS_Y 40

#define CENTERED 500
#define SENS 45
#define RANGE_POS (CENTERED + SENS)
#define RANGE_NEG (CENTERED - SENS)
int apretado=0;
int main_stick(void)
{
  int analog_in_xr;
  int analog_in_yr;
  int analog_in_xl;
  int analog_in_yl;
 /*  int last_input_xr = analog_in_xr;
  int last_input_yr = analog_in_yr; */
  
  
  serial_put_str("\rStick start\r\n");
  while(1){
    analog_in_xr=adc_get(0); //Valores de 0 a 1023 !Este llega a 1020
    analog_in_yr=adc_get(1); //Valores de 0 a 1023 
    analog_in_xl=adc_get(2); //Valores de 0 a 1023 !Este llega a 1020
    analog_in_yl=adc_get(3); //Valores de 0 a 1023 

    //Centered stick: (511, 495)


    /* if(analog_in_xr > last_input_xr+2 || analog_in_xr < last_input_xr-2 || analog_in_yr > last_input_yr+2 || analog_in_yr < last_input_yr-2){
      last_input_xr=analog_in_xr;
      serial_put_int(analog_in_xr, 4);
    } */
    /* if(analog_in_xr > last_input_xr+2 || analog_in_xr < last_input_xr-2 || analog_in_yr > last_input_yr+2 || analog_in_yr < last_input_yr-2){
      last_input_xr=analog_in_xr;
      last_input_yr=analog_in_yr;
      set_mov_base(analog_in_xr, analog_in_yr);
      //todo mando analog + numero servo y hago 4 llamadas a la misma funcion
    } */

    adjust_servo_angle(0, analog_in_xr);
    adjust_servo_angle(1, analog_in_yr);
    adjust_servo_angle(2, analog_in_xl);
    adjust_servo_angle(3, analog_in_yl);
    stick_click();
    /* 
     Cuando se detecten variaciones en x o y llamar a metodo que detecte index y direction
     de ahi se llama a justar serv angle
     */
  } 
}

//SERVOS 0,1
/* int set_mov_base(int analog_in_x, int analog_in_y){
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
    if(servo_index_y > -1 && direction_y > -1){
      adjust_servo_angle(servo_index_y, direction_y);
    }
} */

//todo aca recibir valor analogico y poner el if de linea 69 aca dentro
void adjust_servo_angle(int servo_index, int analog_in)
{
  int direction = -1;
  if(analog_in > (RANGE_POS)){
    direction=0;
  }else if(analog_in < (RANGE_NEG)){
    direction=1;
  }else{return}

  if (direction==0 && servo_angles[servo_index] > 0)
  {
    servo_angles[servo_index] -= ANGLE_STEP;
  }else if (direction==1 && servo_angles[servo_index] < 100) //!Con rango [0,100] llega a 2ms
  {
    servo_angles[servo_index] += ANGLE_STEP;
  }
  
  servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
  print_array();
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
	return TICKS_UNTIL_1ms + angle;
}

void stick_click(){
  int bitIn = *(PIN_D) & 0b00000100;
  volatile long i=0;
  int bitEncendido= *(PUERTO_B) & 0b00100000;//Obtengo estado
    
  if((bitIn == 0) /* && (apretado == 0) */){//Si apretó y no venia pulsando 
    /* for(i=0; i<1000; i++){}  */
    if(bitEncendido == 0){//Si estaba apagado lo prende
      cli();
      *(PUERTO_B) |= 0b00100000;//Prende PB5=d13
      sei();
    }else{//Si estaba prendido lo apaga
      cli();
      *(PUERTO_B) &= 0b11011111;//Apaga PB5=d13
      sei();
    } 
    apretado=1; 

    
  }

  /* if(bitIn!=0 && apretado==1){ //Si deje de pulsar y venia pulsando
  /* for(i = 0; i < 1000; i++){} */
    /* cli();
    *(PUERTO_B) &= 0b11011111;//Apaga PB5=d13
    sei();
    apretado=0;
  } */ 
}


