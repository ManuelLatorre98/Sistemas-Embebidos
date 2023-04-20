int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  volatile unsigned char * PIN_B= (unsigned char *) 0X23;

  *(DDR_B)= 0b00100111;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00001000;//Habilita pullup en pin pb3 y enciende pines pb0, pb1, pb2 
  int apretado=0;
 
  while(1){
    int bitIn = *(PIN_B) & 0b00001000;
    volatile long i=0;
    int bitEncendido= *(PUERTO_B) & 0b00100000;//Obtengo estado
    
    if(bitIn==0 && apretado==0){//Si apretó y no venia pulsando 
      for(i=0; i<10000; i++){} 
      if(bitEncendido==0){//Si estaba apagado lo prende
        *(PUERTO_B)= *(PUERTO_B) | 0b00100000;//Prende PB5=d13
      }else{//Si estaba prendido lo apaga
        *(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
      }
      apretado=1;
    }

    if(bitIn!=0 && apretado==1){ //Si deje de pulsar y venia pulsando
      //*(PUERTO_B)= *(PUERTO_B) & 0b11011111;//Apaga PB5=d13
      for(i=0; i<10000; i++){} 
      apretado=0;
    }
  }
}