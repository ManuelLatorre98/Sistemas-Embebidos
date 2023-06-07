#include <xinu.h>
#include "serial.h"
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
int main_motor(void)
{
	int analog_in;
  int encedido=0;
  int bit_in = 0;
  *(DDR_B)= 0b00100000;//bit 5= led arduino, 
  *(PUERTO_B)= 0b00100001;//Habilita pullup en pin pb0
  adc_init();
  serial_init();
  while(1){
    bit_in = *(PIN_B) & 0b00100000;
    analog_in = (adc_get(0)/102); //Aca para tener 10 valores del 0 al 9 y poder distribuir: izq:0,1,2 med=3,4,5,6 der=7,8,9
    //MOVIMIENTO IZQ/DER

    if(!bit_in){
      *(PUERTO_B)= *(PUERTO_B) | 0b00100000;
      
    }else{
      *(PUERTO_B)= *(PUERTO_B) & 0b11011111;
    }
    
    serial_put_int(analog_in,4);
    serial_put_str("\r\n");
    //65000: 16 bits
    if(!analog_in){
      sleepms(30);
    }else{
      sleepms(50*analog_in);
    }
    
  }
}
