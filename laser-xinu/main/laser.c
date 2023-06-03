#include <xinu.h>
#include "serial.h"
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
int mainLaser(void)
{
	char rcv_char=' ';
	serial_init();
  (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
	serial_put_string("EJECUTANDO.\r\n");
  for(;;){
    (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
    serial_put_string("\rIngrese una letra: \r\n");
    rcv_char = serial_get_char();
    serial_put_char(rcv_char);
    serial_put_string("\r\n");
    print(rcv_char);
    serial_put_char('\r');
    serial_put_char('\n');
    serial_put_string("ARRANCA.\r\n");
    prende_apaga(rcv_char);
  }
}

void prende_apaga(char letra)
{
  
  //volatile int send=0;
  volatile int i;
  volatile int bit;
  volatile int gap= 200;
  *(PUERTO_B)= 0b00000001;
  volatile int aux;
  //timer0_init();
  //sei();

  (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
  sleepms(gap);
  (*PUERTO_B)= (*PUERTO_B) & 0b11111110; //señal de bajada

  /* cli();//disable interrupt
      send=0;
  sei(); //enable interrupt */

  //BIT
  for(i = 0; i < 8; i ++){   
    /* while(!send){} */
    sleepms(gap);
    /* if(send){
      cli();//disable interrupt
      send=0;
      sei(); //enable interrupt */
      bit = ((int)(letra >> i) & 0x01);//obtiene bit a bit
      if(bit){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
      }else{
        (*PUERTO_B)= (*PUERTO_B) & 0b11111110; //off
      }
    //}
  }
  sleepms(gap);
  /* while(!send){} */

}

void print(char rcv_char){
  volatile int i;
  volatile int bit;
    for(i = 0; i < 8; i ++){
        bit = ((int)(rcv_char >> i) & 0x01);
        serial_put_int(bit , 4);
        serial_put_char('\r');
        serial_put_char('\n');
    }
}