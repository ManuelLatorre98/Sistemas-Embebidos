int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  volatile unsigned char * PIN_B= (unsigned char *) 0X23;

  *(DDR_B)= 0b00100111;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00101111;//Habilita pullup en pines 1,2,3 pb0..pb1
  //*(PIN_B)= 0b00001000;//indica que el pin 1,2 y 3 son entradas

 

  while(1){
    int bitIn = *(PIN_B) & 0b00001000;
    if(bitIn==0){//Varia en funcion de la entrada (osea el pulsador)
      //METER DELAY DE REBOTE DE PULSADOR
      volatile long i=0;
      for(i=0; i<10000; i++){} 
      
      //DELAY
      *(PUERTO_B)= *(PUERTO_B) & 0b11111110;//Apaga PB0=d8
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) || 0b00000010;//Prende
      
      //DELAY
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) & 0b11111101;//Apaga PB1=d9
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) || 0b00000100;//Prende

      //Delay
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) & 0b11111011;//Apaga PB10
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) || 0b00000001;//Prende 
      for(i=0; i<10000; i++){} //delay 
    }
  }



}