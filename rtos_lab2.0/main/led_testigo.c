#include <xinu.h>
#include "serial.h"
#include "globals.h"
/* volatile int initiated_led=0; */
int bit_in = 0;

int main_led_testigo(void)
{
  *(DDR_B)= 0b00100000;//bit 5= led arduino, 
  *(PUERTO_B)= 0b00000001;//Habilita pullup en pin pb0
  while(1){
    //check_estado_led();
    bit_in = *(PIN_B) & 0b00100000;//Revisa estado actual del led
    if(motor_init){
      parpadeo();
    }else{
      if(bit_in){
        (*PUERTO_B) &= ~(1 << 5);//Apaga
      }
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}

void parpadeo()
{
  

  if(!bit_in){
    *(PUERTO_B) |= (1 << 5);//Prende
  }else{
    (*PUERTO_B) &= ~(1 << 5);//Apaga
  }

  if(motor_speed==0){//Velocidad minima
    sleepms(500);
  }else if(motor_speed==10){//Velocidad maxima
    sleepms(30);
  }else{
    sleepms(500/motor_speed);
  }
}

/* void check_estado_led()
{ 
  if(!motor_init || !initiated_led){//Si venia apagado y se prende
    (*PUERTO_B) &= ~(1 << 5); //Apaga led arduino
    initiated_led=0;
    sync_wait(SEM_LED);//Se bloquea hasta que lo desbloquee el main
    initiated_led=1;
  }
} */


