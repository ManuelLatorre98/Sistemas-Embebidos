#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
//volatile int initiated_motor=0;
int main_motor(void)
{
  *(DDR_B)= 0b00100000;//bit 5= led arduino, 
  *(PUERTO_B)= 0b00000001;//Habilita pullup en pin pb0
  while(1){
    if(motor_init){
      motor_speed = (adc_get(0)/102);//10 posibles valores
      timer1_motor(motor_speed);
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}



