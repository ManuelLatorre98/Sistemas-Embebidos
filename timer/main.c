#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer.h"

void main()
{
  *(DDR_B)= 0b00000001;//bit 0 = salida
  *(PUERTO_B)= 0b00000001;
  volatile int aux;
  timer0_init();
  sei();
  for(;;){
    cli();//disable interrupt
      aux=encendido;
    sei(); //enable interrupt
    if(aux){
      (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
    }else{
      (*PUERTO_B)= (*PUERTO_B) & 0b11111110; //off
    }
    
  }
}