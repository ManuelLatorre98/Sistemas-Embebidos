#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
//volatile int initiated_motor=0;
int main_motor(void)
{
  serial_put_char('M');
  while(1){
    serial_put_char('N');
    if(motor_init){
      motor_speed = (adc_get(0)/102);//10 posibles valores
    
      timer1_motor(motor_speed);
    }else{
      timer1_motor(0);
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}



