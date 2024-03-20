#include <stdint.h>
#include <avr/interrupt.h>
#include "timer2.h"
#include "globals.h"
/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b00000001 // [COM2A1|COM2A0]  clear on match  - [WGM21|WGM20] fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00000001 // [WGM22]         fast PWM        - [CS22|CS21|CS20]      prescaler 8

/********************** Calculos de valores ***************************
 *
 * f_cpu/prescaler = 16000000/8 = 2000000 t/s
 * FREQ: 2000000 t/s * 0.020  = 40000 = 0x9c40
 * MIN:  2000000 t/s * 0.001  = 2000  = 0x07d0
 * MAX:  2000000 t/s * 0.002  = 4000  = 0x0fa0
 **********************************************************************/

/********************** Calculos de valores ***************************
 *
 * f_cpu/prescaler = 16000000/64 = 250000 t/s
 * FREQ: 250000 t/s * 0.020  = 40000 = 0x9c40
 * MIN:  2000000 t/s * 0.001  = 2000  = 0x07d0
 * MAX:  2000000 t/s * 0.002  = 4000  = 0x0fa0
 **********************************************************************/

/* Macros de valores */
#define TICKS_UNTIL_INTERRUPT 10000


/* Estructura de datos del driver TIMER */
typedef struct
{
    uint8_t control_reg_a;      // TCCR2A
    uint8_t control_reg_b;      // TCCR2B
    uint8_t counter_reg;        // TCNT2
    uint8_t out_compare_reg_a;      // OCR2A
    uint8_t out_compare_reg_b;      // OCR2B
} volatile timer2_t;
volatile timer2_t *timer2 = (timer2_t *)0xB0; // Direccion base

//INTERRUPCIONES. NO LOS USO
volatile uint8_t *timer_interrupt_mask_reg_t2 = (uint8_t *)0x70; // TIMSK2
/* volatile uint8_t *timer_interrupt_flag_reg_t2 = (uint8_t *)0x37; // TIFR2 (no se si sirve de algo) */

void timer2_init()
{
    /* setear la configuracion del timer2 */
    timer2->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
    timer2->control_reg_b |= CONF_CONTROL_REG_B_FPWM;


    uint16_t ocr_value = TICKS_UNTIL_INTERRUPT; 

    /* determinar la frecuencia con el registro OCR2A */
    timer2->out_compare_reg_a = (uint8_t)(ocr_value >> 8);
    
    *timer_interrupt_mask_reg_t2 |= 2;
}

int ticks2 = 0;
// Función de interrupción del timer (Deberia ejecutarse cada 2ms)
ISR(TIMER2_COMPA_vect) 
{
  ticks2++;
  if(ticks2==1000){
    /* paso un segundo */  
    encendido=!encendido;
    ticks2=0;
  }
}

