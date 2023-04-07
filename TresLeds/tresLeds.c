int encendido=0;
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
int apretado=0;
int main(void)
{
  *(DDR_B)= 0b00100111;//bit 5= led arduino,bit 3= pinb (entrada)
  *(PUERTO_B)= 0b00001001;//Habilita pullup en pin pb3 y enciende pines pb0, pb1, pb2 
  
  while(1){//
    volatile long i=0;
    encenderApagar();
    while(encendido==0){encenderApagar();} //Con esto me aseguro que siempre arranca aca cada vez que apreta el boton
      if(encendido==1){
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay prendido
        
        *(PUERTO_B)= *(PUERTO_B) & 0b11111110;//Apaga PB0=d8
      
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay apagado
      }
      if(encendido==1){
        *(PUERTO_B)= *(PUERTO_B) | 0b00000010;//Prende PB1=d9
        
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay prendido
      }

      if(encendido==1){
        *(PUERTO_B)= *(PUERTO_B) & 0b11111101;//Apaga PB1=d9
      
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay apagado
      }
      if(encendido==1){
        *(PUERTO_B)= *(PUERTO_B) | 0b00000100;//Prende PB2=d10
        
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay prendido
      }
      if(encendido==1){
        *(PUERTO_B)= *(PUERTO_B) & 0b11111011;//Apaga PB2=d10
        
        for(i=0; i<10000; i++){
          encenderApagar();
        } //delay apagado
      }
      if(encendido==1){
        *(PUERTO_B)= *(PUERTO_B) | 0b00000001;//Prende PB0=d8
      }

  }
}

void encenderApagar(){
  volatile int bitIn = *(PIN_B) & 0b00001000;
  volatile long i=0;
  
  if(bitIn==0 && apretado==0){//Si apretó y no venia pulsando 
    for(i=0; i<10000; i++){} 
    if(encendido==0){//Si estaba apagado lo prende
      *(PUERTO_B)= *(PUERTO_B) | 0b00100001;
      encendido=1;
    }else{//Si estaba prendido lo apaga
    *(PUERTO_B)= *(PUERTO_B) & 0b11011000;
      encendido=0;
      
    }
    apretado=1;
  }

  if(bitIn!=0 && apretado==1){ //Si deje de pulsar luego de estar pulsando
    for(i=0; i<10000; i++){} 
    apretado=0;
  }
}
