/* #include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
#include "timer2.h"
volatile int last_angle_array={0,0,0,0};
int main_servo(void)
{
  volatile int servo_angles_len = sizeof(servo_angles) / sizeof(mi_array[0]);
  while(1){
    for(int i = 0; i<servo_angles_len; i++){
      if(last_angle_array[i] != servo_angles[i]){
        last_angle_array[i] = servo_angles[i];
        //serial_put_int(last_angle,3);
      } 
      sleep(0.001);//Para que libere CPU y pueda correr main
    }
    
  }
} */




