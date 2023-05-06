#include "adc.h"
#include "serial.h"
#include "sleep.h"
main(void)
{
  int analog_in;
  int ohm;
  adc_init();
  serial_init();
  while(1){
    analog_in = (adc_get(0)/28);
    sleep_ms(400);
    sleep_ms(400);
    serial_put_int(analog_in, 6);
    serial_put_string("\n\r");
  }
  //dividir por 28 sumar 48 para rango de acii
}