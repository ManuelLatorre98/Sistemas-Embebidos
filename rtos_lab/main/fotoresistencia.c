#include <xinu.h>
#include "adc.h"
#include "serial.h"
#include "globals.h"
#include <avr/interrupt.h>
void fotoresis(void)
{
  int analog_in;
  adc_init();
  serial_init();
  while(1){
    analog_in = (adc_get(1)); //8bits = (adc_get(0)/28), 12 bits= (adc_get(0)/455)
    sleepms(400);
    serial_put_int(analog_in, 4);
    serial_put_str("\n\r");
  }
}