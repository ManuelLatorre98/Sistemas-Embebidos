#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
#include <avr/interrupt.h>
#include "adc.h"
/* definicion de tareas (cuyo codigo fuente es externo) */
#define TICKS_UNTIL_1ms 182
extern int main_stick(void);
int main(void)
{
	char rcv_char = ' ';
	*(DDR_B) = 0b00111111;		// bit 5= led arduino, pb0,1,2,3,4 = salidas de servos
	*(PUERTO_B) = 0b00111111; // Arranca con las señales todas en alto.
	*(DDR_D) = 0b00000000;		// pd2 entrada
	*(PUERTO_D) = 0b00000100; // Activo pullup
	// sleep(5);
	timer1_init();
	serial_init();
	adc_init();
	/* creamos y ponemos a ejecutar las tareas */
	resume(create(main_stick, 512, 30, "sti", 0));
	/* resume(create(main_show_data, 60, 30, "sho", 0)); */

	/* sleep(1); */ //Le doy tiempo a las tareas a iniciar y que no se rompan los print
	serial_put_str("\rRTOS_LAB INICIADO\r\n");
	sleep(10);	
	serial_put_str("\rCONTINUA SEM\r\n");
	while (1)
	{
	}
	return 0;
}