int main(void)
{
  volatile unsigned char * DDR_B = (unsigned char *) 0x24;
  volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
  *(DDR_B)=32;
  volatile long i=0;
  while(1){
    *(PUERTO_B) = 0;
    for(i=0; i<100000; i++){} //delay prendido
    *(PUERTO_B) = 0;
    
    for(i=0; i<100000; i++){} //delay apagado
  }
}