#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
/* definicion de tareas (cuyo codigo fuente es externo) */

extern int main_motor(void);
extern int main_led_testigo(void);
extern int main_cervo(void);

/* main es una tarea independiente y se la utiliza como tal */
int main(void)
{
	char rcv_char=' ';
	serial_init();
	adc_init();
	timer1_init();
	/* creamos y ponemos a ejecutar dos tareas */
	
	resume(create(main_motor, 256, 30, "motr", 0));
	resume(create(main_led_testigo, 256, 30, "led", 0));
	resume(create(main_cervo, 256, 30, "cerv", 0));
	
	serial_put_str("\rRTOS_LAB INICIADO\r\n");

	
	while(1) {
		if(serial_getchar_ready()){
			rcv_char= serial_get_char();
			serial_put_char(rcv_char);
			if(rcv_char == 'n'){//Recibe n entonces enciende
				if(!motor_init) serial_put_str("\rMOTOR ENCENDIDO\r\n");
				motor_init=1;
			}else if(rcv_char == 'b'){
				if(motor_init) serial_put_str("\rMOTOR APAGADO\r\n");
				motor_init=0;
			}else if(rcv_char == 'a' || rcv_char == 'd' ){
				adjust_cerv_angle(rcv_char);	
  		}
		}
		sleepms(1);
	}
	return 0;
}

void adjust_cerv_angle(char rcv_char){
	if(rcv_char=='a'){
		if(cerv_angle>0){
			cerv_angle-=20;
		}
	}else if(rcv_char=='d'){
		if(cerv_angle<180){
			cerv_angle+=20;
		}
	}
}