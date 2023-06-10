#include <xinu.h>
#include "serial.h"
#include "globals.h"
#define SEM_MOTOR 0
volatile int initiated_motor=0;
int main_motor(void)
{
  int bit_in = 0;
  *(DDR_B)= 0b00100000;//bit 5= led arduino, 
  *(PUERTO_B)= 0b00000001;//Habilita pullup en pin pb0
  while(1){
    check_estado();
    motor_speed = (adc_get(0)/102);//10 posibles valores

  }
}

void check_estado()
{ 
  if(!motor_init || !initiated_motor){//Si venia apagado y se prende
    initiated_motor=0;
    sync_wait(SEM_MOTOR);//Se bloquea hasta que lo desbloquee el main
    initiated_motor=1;
  }
}


