#include "globals.h"
void print_angles()
{
  //!Se imprimen valores entre 90 y 270 ya que esos son los ticks entre 1ms y 2ms (representan los 180° del servo)
	serial_put_str_inline("[");
	for(int i = 0; i<N_SERVOS; i++){
		serial_put_int(servo_ticks[i],3);
    serial_put_str_inline(", ");
	}
  serial_put_str_inline("] ");
}
