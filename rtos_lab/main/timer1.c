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
#define CONF_CONTROL_REG_A_FPWM 0b10100010; // [COM1A1|COM1A2] [COM1B1|COM1B2]  clear on match  - [WGM11|WGM10]         fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00011010; // [WGM13|WGM12]    fast PWM        - [CS02|CS01|CS00]      preescale 8
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

/* Macros de valores */
#define TICKS_UNTIL_1ms 500
#define TICKS_UNTIL_2ms 1000
#define TICKS_UNTIL_20ms 10000
#define TICK_OFFSET 2.777 // 0x07d0
#define CLOCK_FREQ = 16000000
#define PRESCALER = 8

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

volatile int ticks;
volatile int servo_angles_len = sizeof(servo_angles) / sizeof(mi_array[0]);
uint8_t pinMask;

int timer1_init()
{
	/* setear la configuracion del timer1  */
	timer->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
	timer->control_reg_b |= CONF_CONTROL_REG_B_FPWM;
	timer->control_reg_c |= CONF_CONTROL_REG_C_FPWM;

	uint16_t ocr_value = 1; // Quiero una interrupción cada 2us

	/* Determinamos el ancho de la señal en alto en cada ciclo con el registro OCR1A */
	timer->out_compare_reg_ah = (uint8_t)(ocr_value >> 8); // Byte alto de OCR1A
	timer->out_compare_reg_al = (uint8_t)(ocr_value & 0xFF); // Byte bajo de OCR1A

	/* Habilito interrupciones del timer1 para el registro A */
	timer_interrupt_mask_reg |= (1 << 1);
	return 0;
}

// Función de interrupción del timer (Deberia ejecutarse cada 2ms)
ISR(TIMER1_COMPA_vect) {
	ticks++;
	if(ticks == TICKS_UNTIL_20ms) //Fin del ciclo del servo
	{
		ticks=0;
		for(int i = 0; i<servo_angles_len; i++){
			pinMask= 1<<i; 
			(*PUERTO_B)|=pinMask; //pin up a cada pin
			servo_angles[i]=0; //
		}
	}else{
		for(int i = 0; i<servo_angles_len; i++){
			if(ticks == getTicksOffset(servo_angles[i]))
			{ //Si estoy en los ticks que pide el servo
				pinMask= 0<<i; 
				(*PUERTO_B)|=pinMask; //Pin down sobre el servo
			}
		}
	}
}

int getTicksOffset(int angle)
{
	return TICKS_UNTIL_1ms + (angle* 2.777);
}
