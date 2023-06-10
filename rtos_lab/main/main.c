/* main.c: programa ejemplo con tres tareas concurrentes.
 *
 * tarea_led: prioridad 20, pila 64 bytes.
 * tarea_comunicaciones: prioridad 20, pila 256 bytes
 * tarea_main: prioridad 20, pila 256 bytes
 *
 * dos semaforos para sincronizar una alternancia de uso del UART
 */

#include <xinu.h>
#include "serial.h"
#include "globals.h"
/* definicion de tareas (cuyo codigo fuente es externo) */

extern int main_motor(void);
extern int main_led_testigo(void);
/* extern int comunicacion(void); */

/* nombre para dos semaforos a utilizar */
#define SEM_MOTOR 0
#define SEM_LED 0
/* main es una tarea independiente y se la utiliza como tal */
int main(void)
{
	char rcv_char=' ';
	serial_init();
	adc_init();
	/* inicializamos los semaforos */
	sync_set(SEM_MOTOR,0);
	sync_set(SEM_LED,0);
	/* creamos y ponemos a ejecutar dos tareas */
	resume(create(main_motor, 256, 30, "motr", 0));
	resume(create(main_led_testigo, 256, 30, "led", 0));


	
	while(1) {
		if(serial_getchar_ready()){
			rcv_char= serial_get_char();
			serial_put_char(rcv_char);
			if(rcv_char == 'n'){//Recibe n entonces enciende
				serial_put_str("\rMOTOR ENCENDIDO\r\n");
				motor_init=1;
				sync_signal(SEM_MOTOR);
				sync_signal(SEM_LED);//Para el motor
				//sync_signal(SEM_MOTOR);//Para el led testigo
			}else if(rcv_char == 'b'){
				if(motor_init){
					serial_put_str("\rMOTOR APAGADO\r\n");
				}
				motor_init=0;
			}
  	}
	}

	return 0;
}


