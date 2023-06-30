#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
volatile int last_angle=0;
int main_cervo(void)
{
  
  while(1){
    if(last_angle != cerv_angle){
      timer1_cervo(cerv_angle);
      last_angle=cerv_angle;
      serial_put_int(last_angle,3);
    }
    //sleepms(1);//Para que libere CPU y pueda correr main
  }
}




