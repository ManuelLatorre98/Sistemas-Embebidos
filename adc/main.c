#include "adc.h"
#include "serial.h"
#include "sleep.h"
main(void)
{
  int analog_in;
  adc_init();
  serial_init();
  serial_put_int(14, 2);
  while(1){
    analog_in = (adc_get(0));
    sleep_ms(500);
    serial_put_int(analog_in, 5);
  }
  //dividir por 28 sumar 48 para rango de acii
}