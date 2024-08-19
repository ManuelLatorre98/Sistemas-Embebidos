#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include <avr/interrupt.h>
#define ANGLE_STEP 5
//Valores analogicos del stick. Defino la sensibilidad para evitar ajustes cuando se vuelve a centrar

#define CENTERED 500
#define SENS 60
#define RANGE_POS (CENTERED + SENS)
#define RANGE_NEG (CENTERED - SENS)
int apretado=0;
void main_stick(void)
{
  int analog_in_xr;
  int analog_in_yr;
  int analog_in_xl;
  int analog_in_yl;
  /* int last_input_xr = analog_in_xr;
  int last_input_yr = analog_in_yr; */
  
  initialPrint();
  while(1){
    analog_in_xr = adc_get(0); 
    analog_in_yr = adc_get(1); 
    analog_in_xl = adc_get(2); 
    analog_in_yl = adc_get(3);

    /* 
    Calcular limites de los adc_get. 
    Esos limites son los que me tiene que imprimir el handcontroller al adc
    Envio los resultados por el adc como caracteres. Usar $ para indicar el final de linea.
    Ese resultado va a ser analog_in_yl
    Una vez tengo un valor lo mando con adjust_servo_angle(3, analog_in_yl)
    */

    adjust_servo_angle(0, analog_in_xr);
    adjust_servo_angle(1, analog_in_yr); 

    //!(Si solo hay un stick conectado, debo indicar explicitamente que esta centrado
    adjust_servo_angle(2, analog_in_xl); //Todo analog_in_xl 
    adjust_servo_angle(3, analog_in_yl); //Todo analog_in_yl
    
    //Parametros stick_click: (nro servo, nro stick, entrada analogica)
    int bitInL = *(PIN_D) & 0b00000100;
    int bitInR = *(PIN_D) & 0b00001000;
    stick_click(4,0,bitInL); //0 = left stick, 
    stick_click(4,1,bitInR); //1 = right stick
  } 
}

void adjust_servo_angle(int servo_index, int analog_in)
{
  int direction = -1;
  int update_ticks= 0;
  if(analog_in > (RANGE_POS)){
    direction = 0;
  }else if(analog_in < (RANGE_NEG)){
    direction = 1;
  }else{return;}

  if(direction != -1){
    if (direction == 0 && servo_angles[servo_index] > 0)
    {
      servo_angles[servo_index] -= ANGLE_STEP;
      update_ticks=1;
    }else if (direction == 1 && servo_angles[servo_index] < 180)
    {
      servo_angles[servo_index] += ANGLE_STEP;
      update_ticks=1;
    }
    
    if(update_ticks){
      servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
      print_angles();

    }
  }
}


void stick_click(int servo_index, int stick, int bitIn){
  int update_ticks= 0;
  if((bitIn == 0)){//Si apretó
    sleepms(10);
    if(stick == 0 && servo_angles[servo_index] > 0){//Si es el stick izquierdo achica y no esta en tope
      servo_angles[servo_index] -= ANGLE_STEP;
    }else if(stick == 1 && servo_angles[servo_index] < 180){//Si es el stick derecho agranda y no esta en tope
      servo_angles[servo_index] += ANGLE_STEP;
    }
    update_ticks=1;
    apretado=1; 
  }

  if(bitIn!=0 && apretado==1){ //Si deje de pulsar y venia pulsando
    sleepms(10);
    update_ticks=0;
    apretado=0;
  }

  //Si estoy en los limites no imprimo
  if((stick == 0 && servo_angles[servo_index] < 0) || (stick == 1 && servo_angles[servo_index] > 180)){
    update_ticks=0;
  }

  //Impresion angulos
  if(update_ticks){
    servo_ticks[servo_index] = getTicksOffset(servo_angles[servo_index]);
    print_angles();
  }
} 

int getTicksOffset(int angle)
{
	return TICKS_UNTIL_1ms + angle;
}
void initialPrint(){
  sleepms(400);
  serial_put_str("ANGULOS DE LOS SERVOS: ");
	print_angles();
}