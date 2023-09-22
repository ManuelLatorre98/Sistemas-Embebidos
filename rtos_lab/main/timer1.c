/**********************************************************************
 *
 * timer1.c - Driver del TIMER 1 (16 bits) del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>
#include <avr/interrupt.h>
#include "globals.h"
#include "timer1.h"
#include "serial.h"


/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b10100000; // [COM1A1|COM1A2] [COM1B1|COM1B2]  clear on match  - [WGM11|WGM10]         fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00001001; // [WGM13|WGM12]    fast PWM        - [CS02|CS01|CS00]      preescale 8
#define CONF_CONTROL_REG_C_FPWM 0b00000000; //

/********************** Calculos de valores ***************************
 *
 * f_cpu/prescalar = 16000000/8 = 2000000 t/s = 2 ticks por us
 * 1000us/2t/us = 500 ticks necesarios para llegar a 1ms
 * 1000 ticks necesarios para llegar a 2ms
 * 500*20 = 10000 ticks para llegar a 20ms (FIN DE CICLO DEL SERVO)
 * Tengo 500 posibles valores para indicar angulos
 * 500 / 180 = 2.777
 * Si recibo valores entre 0 y 180 hago 500 + (val*2.777) = cantidad de ticks necesarios (que va en el array de los servos)
 *

 **********************************************************************/
/********************** Calculos de valores ***************************
 *
 * f_cpu/prescalar = 16000000/1 = 16000000 t/s = 16 ticks por us
 * 1000us/16t/us = 16000 ticks necesarios para llegar a 1ms
 * 32000 ticks necesarios para llegar a 2ms
 * 16000*20 = 320000 ticks para llegar a 20ms (FIN DE CICLO DEL SERVO)
 * Tengo 16000 posibles valores para indicar angulos
 * 16000 / 180 = 88.8888889
 * Si recibo valores entre 0 y 180 hago 500 + (val*88.9) = cantidad de ticks necesarios (que va en el array de los servos)
 * Quiero interrumpir cada 5.5us entonces 16*5=80ticks en 0,5us=8ticks --> 5.5us=88ticks
 *

 **********************************************************************/
/* Macros de valores */
#define TICKS_UNTIL_1ms 16000
#define TICKS_UNTIL_2ms 32000
#define TICKS_UNTIL_20ms 320000
#define TICK_OFFSET 88.888 
#define TICKS_UNTIL_INTERRUPT 88
#define CLOCK_FREQ 16000000
#define PRESCALER 1

/* #define MIN_PWM_8P 0x03e8				// 0x07d0
#define MAX_PWM_8P_SERVO 0x1130 // 0x0f9f
#define MAX_PWM_8P_MOTOR 0x9c3f
#define TIMER1_FREQ_H 0x9c
#define TIMER1_FREQ_L 0x3f
#define TIMER1_0CR1AH_POS 0x0f
#define TIMER1_0CR1AL_POS 0x9f */

/* Estructura de datos del driver TIMER */
typedef struct
{
	uint8_t control_reg_a;			// TCC1RA
	uint8_t control_reg_b;			// TCC1RB
	uint8_t control_reg_c;			// TCC1RC
	uint8_t _reserved;					//
	uint8_t counter_reg_l;			// TCNT1L
	uint8_t counter_reg_h;			// TCNT1H
	uint8_t in_capture_regl;		// ICR1L
	uint8_t in_capture_regh;		// ICR1H
	uint8_t out_compare_reg_al; // OCR1AL
	uint8_t out_compare_reg_ah; // OCR1AH
	uint8_t out_compare_reg_bl; // OCR1BL
	uint8_t out_compare_reg_bh; // OCR1BH
} volatile timer1_t;
volatile timer1_t *timer = (timer1_t *)0x80; // Direccion base

volatile uint8_t *timer_interrupt_mask_reg = (uint8_t *)0x6f; // TIMSK1
//volatile uint8_t *timer_interrupt_flag_reg = (uint8_t *)0x36; // TIFR1 (no se si sirve de algo)

unsigned long int ticks = 0;
uint8_t pinMask;

int timer1_init()
{
	/* setear la configuracion del timer1  */
	timer->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
	timer->control_reg_b |= CONF_CONTROL_REG_B_FPWM;
	timer->control_reg_c |= CONF_CONTROL_REG_C_FPWM;

	uint16_t ocr_value = TICKS_UNTIL_INTERRUPT; // Quiero una interrupción cada 5.5us=88ticks

	/* Determinamos el ancho de la señal en alto en cada ciclo con el registro OCR1A */
	timer->out_compare_reg_ah = (uint8_t)(ocr_value >> 8); // Byte alto de OCR1A
	timer->out_compare_reg_al = (uint8_t)(ocr_value & 0xFF); // Byte bajo de OCR1A

	/* Habilito interrupciones del timer1 para el registro A */
	*timer_interrupt_mask_reg |= 2;
	return 0;
}

unsigned long int getTicksOffset(int angle)
{
  unsigned long int result= TICKS_UNTIL_1ms + (angle * TICK_OFFSET);
	return result;
}
// Función de interrupción del timer (Deberia ejecutarse cada 2ms)
ISR(TIMER1_COMPA_vect) {
	ticks++;
  if(ticks==300000){
    (*PUERTO_B)=0;
  }else if(ticks==600000){
    (*PUERTO_B)=7;
    ticks=0;
  }
  //(*PUERTO_B)=0;
	/* if(ticks == 320000) //Fin del ciclo del servo
	{
		ticks=0;
		for(int i = 0; i<N_SERVOS; i++){
			pinMask= (1<<i); 
			(*PUERTO_B)|=pinMask; //pin up a cada pin
			//servo_angles[i]=0; //
		}
	}else if(ticks>=16000 && ticks<=32000){
    for(int i = 0; i<N_SERVOS; i++){
			if(ticks == getTicksOffset(servo_angles[i]))
			{ //Si estoy en los ticks que pide el servo
				pinMask= (0<<i); 
				(*PUERTO_B)&=pinMask; //Pin down sobre el servo
			}
		}
  } */
		
}


