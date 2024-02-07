#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer1.h"
#include "timer2.h"

void main()
{
  *(DDR_B)= 0b00100000;//bit 0 = salida
  *(PUERTO_B)= 0b00100000;
  volatile int aux;
  /* timer1_init(); */
  timer2_init();
  sei();
  for(;;){
    cli();//disable interrupt
      aux=encendido;
    sei(); //enable interrupt
    if(aux){
      (*PUERTO_B)= (*PUERTO_B) | 0b00100000; //on
    }else{
      (*PUERTO_B)= (*PUERTO_B) & 0b11011111; //off
    }
    
  }
}