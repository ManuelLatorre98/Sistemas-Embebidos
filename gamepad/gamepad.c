#include "globals.h"
#include "serial.h"
void main(void)
{
  *(DDR_B)= 0b00100000;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00001110;//Habilita pullup en pin pb3, pb2 y pb1
  serial_init();
  int apretado=0;
 
  while(1){
    int bitInIzq = *(PIN_B) & 0b00001000;
    int bitInMed = *(PIN_B) & 0b00000100;
    int bitInDer = *(PIN_B) & 0b00000010;
    volatile long i=0;
    int bitEncendido= *(PUERTO_B) & 0b00100000;//Obtengo estado
    
    if(bitInIzq==0 /*&& apretado==0*/){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('a');
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      apretado=1;
    }

    if(bitInMed==0 /*&& apretado==0*/){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('b');
      *(PUERTO_B)= *(PUERTO_B) | 0b00000000;//Prende PB5=d13
      apretado=1;
    }

    if(bitInDer==0 /*&& apretado==0*/){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('c');
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      apretado=1;
    }

    /*if(bitIn!=0 && apretado==1){ //Si deje de pulsar y venia pulsando (esto para que no detecte inputs cuando mantiene apretado)
      //*(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
      for(i=0; i<10000; i++){} 
      apretado=0;
    }*/
  }
}