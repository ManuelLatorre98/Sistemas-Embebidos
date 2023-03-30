int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  volatile unsigned char * PIN_B= (unsigned char *) 0X23;

  *(DDR_B)= 0b00100111;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00001001;//Habilita pullup en pin pb3 y enciende pines pb0, pb1, pb2 
  
  while(1){
    int bitIn = *(PIN_B) & 0b00001000;
    volatile long i=0;
    if(bitIn==0){//Varia en funcion de la entrada (osea el pulsador)
      for(i=0; i<10000; i++){} 
     
      *(PUERTO_B)= *(PUERTO_B) & 0b11111110;//Apaga PB0=d8
      for(i=0; i<100000; i++){} //delay prendido
      //delay(100000);
      *(PUERTO_B)= *(PUERTO_B) | 0b00000010;//Prende PB1=d9
      
      for(i=0; i<100000; i++){} //delay prendido
      //delay(100000);
      *(PUERTO_B)= *(PUERTO_B) & 0b11111101;//Apaga PB1=d9
      for(i=0; i<100000; i++){} //delay prendido
      //delay(100000);
      *(PUERTO_B)= *(PUERTO_B) | 0b00000100;//Prende PB2=d10

      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) & 0b11111011;//Apaga PB2=d10
      for(i=0; i<100000; i++){} //delay prendido
      *(PUERTO_B)= *(PUERTO_B) | 0b00000001;//Prende PB0=d8
      for(i=0; i<100000; i++){} //delay prendido
    }
  }
}
