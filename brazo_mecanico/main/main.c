#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
#include <avr/interrupt.h>
#include "adc.h"
//#include "fotoresistencia.h"
/* definicion de tareas (cuyo codigo fuente es externo) */

extern void main_stick(void);
int main(void)
{
	char rcv_char = ' ';
	*(DDR_B) = 0b00111111;		// bit 5= led arduino, pb0,1,2,3,4 = salidas de servos
	*(PUERTO_B) = 0b00111111; // Arranca con las señales todas en alto.
	*(DDR_D) = 0b00000000;		// pd2 y pd3 entradas de los sticks
	*(PUERTO_D) = 0b00001100; // Activo pullups

	timer1_init();
	serial_init();
	adc_init();
	/* creamos y ponemos a ejecutar las tareas */
	resume(create(main_stick, 512, 30, "sti", 0));
	sleepms(200);  //Le doy tiempo a las tareas a iniciar y que no se rompan los print
	serial_put_str("\rBRAZO MECANICO INICIADO\r\n");	
	for(;;)

	return 0;
}
