#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
//volatile int initiated_motor=0;
int main_show_data(void)
{
  unsigned int hour;
  unsigned int min;
  unsigned int seg;
  while(1){
    hour = seconds / 3600; // Calcula las horas completas en base a 3600 segundos por hora
    seg = seconds%3600; // Actualiza los segundos restantes después de calcular las horas
    min = seg / 60; // Calcula los minutos completos en base a 60 segundos por minuto
    seg = seg % 60; // Calcula los segundos restantes después de calcular los minutos
    serial_put_int(hour,2);
    serial_put_char(':');
    serial_put_int(min,2);
    serial_put_char(':');
    serial_put_int(seg,2);
    serial_put_str_inline("%. servos:");
    print_servo_array();
    serial_put_str(" ");//Esto me genera un salto de linea
    sleep(1);
  }
}

void print_servo_array(){
  serial_put_str_inline("[");
	for(int i = 0; i<N_SERVOS; i++){
		serial_put_int(servo_angles[i],3);
    serial_put_str_inline(", ");
	}
  serial_put_str_inline("] ");
}

