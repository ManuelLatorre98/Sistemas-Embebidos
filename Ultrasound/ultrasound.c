int encendido=0;
volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;

int sleep10_us(){
  for (volatile int i = 0; i < 1; i++){
  }
  volatile int a=1;
}

void sleep_ms(int tiempo){
  volatile unsigned int cant=146*tiempo;
  for (volatile long i = 0; i < cant; i++){}
}
int main(void)
{
  *(DDR_B)= 0b00100001;//pb5= led arduino, pb3= ENTRADA, pb0=SALIDA
  *(PUERTO_B)= 0b00101001;//Habilita pullup en pin pb3, pb0=Apagado
  volatile unsigned int i;

	serial_init();
  
  int distancia_cm =0;
  unsigned int tiempo_us;
  volatile int echo = 1;
  volatile unsigned int  t;
  volatile int bitIn = *(PIN_B) & 0b00001000;//Chequea el estado inicial de la entrada
  while(1){//
    *(PUERTO_B)= *(PUERTO_B) | 0b00100001;//Activa salida
    sleep10_us();//Espera 10us
    *(PUERTO_B)= *(PUERTO_B) & 0b00101000;//Desactiva salida
    while(!bitIn){}//Se queda esperando que se habilite la entrada

    while(bitIn){
      t++;
      sleep10_us();//Espera 10us
      bitIn = *(PIN_B) & 0b00001000;//Actualiza entrada
    }
    tiempo_us = t * 10;  
    distancia_cm = tiempo_us / 58;
    serial_put_int(distancia_cm);//Mostrar distancia
    sleep_ms(50);//Espera para la siguiente medición
  }
}

