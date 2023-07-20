#include <stdint.h>
#include <avr/interrupt.h>
#include "timer2.h"
#include "serial.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b10100011 // [COM2A1|COM2A0]  clear on match  - [WGM21|WGM20] fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00000101// [WGM22]          fast PWM        - [CS22|CS21|CS20]      prescaler 8

/********************** Calculos de valores TIMER1 ***************************
 *
 * f_cpu/prescaler = 16000000/8 = 2000000 t/s
 * FREQ: 2000000 t/s * 0.020  = 40000 = 0x9c40
 * MIN:  2000000 t/s * 0.001  = 2000  = 0x07d0
 * MAX:  2000000 t/s * 0.002  = 4000  = 0x0fa0
 **********************************************************************/

/********************** Calculos de valores TIMER 2***************************
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
#define MIN_PWM_8P 2000
#define MAX_PWM_8P_SERVO 3999
#define MAX_PWM_8P_MOTOR 0x9c3f
#define TIMER2_FREQ 0x9c3f
#define TIMER1_0CR1AH_POS 0x0f
#define TIMER1_0CR1AL_POS 0x9f


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
/* volatile uint8_t *timer_interrupt_mask_reg_t2 = (uint8_t *)0x70; // TIMSK2
volatile uint8_t *timer_interrupt_flag_reg_t2 = (uint8_t *)0x37; // TIFR2 (no se si sirve de algo) */

int timer2_init()
{
    /* setear la configuracion del timer2 */
    timer2->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
    timer2->control_reg_b |= CONF_CONTROL_REG_B_FPWM;

    /* determinar la frecuencia con el registro OCR2A */
    timer2->out_compare_reg_a = 0;
    timer2->out_compare_reg_b = 0;

    /* reiniciar el registro del contador (por las dudas) */
    timer2->counter_reg = 0;

    return 0;
}

int timer2_servo(int grade)
{
        long int init_value, temp;
        init_value = grade * 100 / 180;//100
        temp = MIN_PWM_8P + (MAX_PWM_8P_SERVO - MIN_PWM_8P) / 100 * init_value;
        temp = temp - MIN_PWM_8P;//Diferencia relativa al valor min
        temp = (temp * 255) / (MAX_PWM_8P_SERVO - MIN_PWM_8P); //Valor normalizado 
        timer2->out_compare_reg_a = temp;
        //1ms=125 2ms=250, entre 140 y 145 cambia


        //Anda con preescalar 8 y el modo 3
        //todo ver señal con osciloscopio
        //!140 se frena, con 100 cambia sentido horario,120retiene mas lento, 160 antihorario
        //!Estoy 40 mas arriba comparado con el comportamiento del timer 1
      
        return 0;
}
