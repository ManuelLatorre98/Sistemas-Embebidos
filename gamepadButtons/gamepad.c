#include "globals.h"
#include "serial.h"
int apretado_i;
int apretado_m;
int apretado_d;
int bit_encendido;
int bit_in_izq;
int bit_in_med;
int bit_in_der;
void main(void)
{
  *(DDR_B)= 0b00100000;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00000111;//Habilita pullup en pin pb3, pb2 y pb1
  serial_init();
  apretado_i=0;
  apretado_m=0;
  apretado_d=0;
  bit_encendido= *(PUERTO_B) & 0b00100000;
 
  while(1){
    
    bit_in_izq = *(PIN_B) & 0b00000001;
    bit_in_med = *(PIN_B) & 0b00000010;
    bit_in_der = *(PIN_B) & 0b00000100;
    volatile long i=0;
    if(bit_in_izq==0){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('a');
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      apretado_i=1;
    }
    
    if(bit_in_med==0){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('b');
      *(PUERTO_B)= *(PUERTO_B) & 0b00100000;
      apretado_m=1;
    }

    if(bit_in_der==0){//Si apretó (Lo comentado va junto al if del final)
      for(i=0; i<10000; i++){} 
      serial_put_char('q');
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      apretado_d=1;
    }
    soltar();
  }
}

void soltar ()
{
  volatile long i=0;
  if(bit_in_izq!=0 && apretado_i==1){ 
      //*(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
      for(i=0; i<10000; i++){} 
      serial_put_string("aq");
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;
      apretado_i=0;
  }else if(bit_in_med!=0 && apretado_m==1){
    for(i=0; i<10000; i++){} 
      serial_put_string("bq");
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;
      apretado_m=0;
  }else if(bit_in_der!=0 && apretado_d==1){
    for(i=0; i<10000; i++){} 
      serial_put_string("cq");
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;
      apretado_d=0;
  }
}