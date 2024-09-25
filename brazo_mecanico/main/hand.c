#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include <avr/interrupt.h>

#define OFFSET 90

void main_hand(void)
{
  initialPrintHand();
  unsigned char rcv_byte;
  while(1){

    if(serial_getchar_ready()){
      rcv_byte = serial_get_char();
      char buffer[50]; 
      int serial_in= (int)rcv_byte;
      //serial_put_char(rcv_byte);
      adjust_servo_angle_hand(0, serial_in);
      //serial_put_int(serial_in,3);
      
      serial_put_str(' ');
      
    }
  } 
}

void adjust_servo_angle_hand(int servo_index, int serial_in)
{

  servo_ticks[servo_index]=serial_in+OFFSET;
  //serial_put_int(servo_angles[servo_index],3);
  print_angles();

}


void initialPrintHand(){
  sleepms(400);
  serial_put_str("ANGULOS DE LOS SERVOS CON HANDCONTROLLER: ");
	print_angles();
}