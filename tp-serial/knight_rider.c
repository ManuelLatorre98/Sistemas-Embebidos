#include "serial.h"
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
int encendido=0;
int apretado=0;
int input=0;
char rcvChar='a';

void knight_rider_run(void)
{
  (*DDR_B)= 0b00110111;//bit 5= led arduino(para debugear),pb3= ENTRADA, pb0,pb1,pb2=SALIDAS
  (*PUERTO_B)= 0b00101001;//Habilita pullup en pin pb3 y enciende pin pb0,
  encendido=1;
  while(encendido){
    verif_pagar();
      if(encendido==1){
        esperar(); //delay prendido
        (*PUERTO_B)= (*PUERTO_B) & 0b11111110;//Apaga pb0=d8
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000010;//Prende pb1=d9
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111101;//Apaga pb1=d9
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000100;//Prende pb2=d10
        
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111011;//Apaga pb2=d10
        
        esperar();//delay apagado
      }
      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001;//Prende pb0=d8
      }
  }
}

void verif_pagar()
{
  
  if(serial_getchar_ready()){
    rcvChar = serial_get_char();
    if(rcvChar == 'q'){//Recibe q entonces apaga
      encendido=0;
      (*PUERTO_B)= 0b00000000; //Apaga led arduino
    }
  }
}

void esperar()
{
  volatile long i=0;
  for(i=0; i<12000; i++){
    verif_pagar();//De esta manera verifica constantemente excepto en los instantes de encendido y apagado que son muy pequeños
  }
}