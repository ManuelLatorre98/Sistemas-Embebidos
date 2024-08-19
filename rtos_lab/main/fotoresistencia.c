#include <xinu.h>
#include "adc.h"
#include "serial.h"
#include "globals.h"
#include <avr/interrupt.h>
void fotoresis(void)
{
  int analog_in_1, analog_in_2;
  adc_init();
  serial_init();
  while(1){
    analog_in_1 = (adc_get(0)); //8bits = (adc_get(0)/28), 12 bits= (adc_get(0)/455)
    analog_in_2 = (adc_get(1)); 
    sleepms(400);

    serial_put_str("0");
    
    serial_put_int(analog_in_1, 4);
    serial_put_str("1");
    serial_put_int(analog_in_2, 4);
    serial_put_str("\n\r");
  }
}