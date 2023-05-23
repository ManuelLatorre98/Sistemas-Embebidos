#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer.h"
#include "recep.h"
#include "serial.h"

void main()
{
  char rcv_char=' ';
  int analog_in;
  int ambient_light;
  int offset;
  int run;
  int bit;
  unsigned char letra;
  adc_init();
  serial_init();
  serial_put_string("EJECUTANDO.\r\n");

  //Obtiene la temperatura ambiente
  analog_in=adc_get(0);
  ambient_light=2875;
  offset=50;
  /*sleep_ms(400);
  sleep_ms(400);
  serial_put_int(ambient_light, 4);
  serial_put_string("\n\r");*/
  timer0_init();
  
  for(;;){
    run=0;
    while(!run){//Espera el inicio de transmision
      if(analog_in<(ambient_light+offset)){//Si recibo la señal en alto constante del laser espero para arrancar, donde se pone en bajo arranca
      run=1;
      sei(); //Arranca las interrupciones
      }
    }
    letra=0; //inicializa el byte en 0b00000000
    //LECTURA
    for(i = 0; i < 8; i ++){   
      while(!send){}//espera 200ms
      
      cli();//disable interrupt
      send=0;
      sei(); //enable interrupt
      //lectura
      if(analog_in > ambient_light+offset){//Si recibo un 1
        letra = (letra << i) | 1 ; //TODO: Podria reemplazar el 1 y el 0 por la condicion del if?
      }else{//Si recibo un 0
        letra = (letra << i) | 0 ;
      }
    }

    //Imprime letra
    serial_put_char(letra);
    serial_put_string("\n\r");
    
  }
  
}
