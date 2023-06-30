#include <stdint.h>
#include <avr/interrupt.h>
#include "timer2.h"
#include "serial.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b10000010 // [COM2A1|COM2A0]  clear on match  - [WGM21|WGM20]         fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00001010 // [WGM22]          fast PWM        - [CS22|CS21|CS20]      prescaler 8

/********************** Calculos de valores ***************************
 *
 * f_cpu/prescaler = 16000000/8 = 2000000 t/s
 * FREQ: 2000000 t/s * 0.020  = 40000 = 0x9c40
 * MIN:  2000000 t/s * 0.001  = 2000  = 0x07d0
 * MAX:  2000000 t/s * 0.002  = 4000  = 0x0fa0
 **********************************************************************/

/* Macros de valores */
#define MIN_PWM_8P 2000
#define MAX_PWM_8P 3999
#define MAX_PWM_8P_CERVO 3999
#define MAX_PWM_8P_MOTOR 0x9c3f
#define TIMER2_FREQ_H 0x9c
#define TIMER2_FREQ_L 0x3f


/* Estructura de datos del driver TIMER */
typedef struct
{
    uint8_t control_reg_a;      // TCCR2A
    uint8_t control_reg_b;      // TCCR2B
    uint8_t _reserved;          //
    uint8_t counter_reg;        // TCNT2
    uint8_t compare_reg_a;      // OCR2A
    uint8_t compare_reg_b;      // OCR2B
} volatile timer2_t;
volatile timer2_t *timer2 = (timer2_t *)0xB0; // Direccion base

volatile uint8_t *timer_interrupt_mask_reg_t2 = (uint8_t *)0x70; // TIMSK2
volatile uint8_t *timer_interrupt_flag_reg_t2 = (uint8_t *)0x37; // TIFR2 (no se si sirve de algo)

volatile int ticks;

int timer2_init()
{
    /* setear la configuracion del timer2 */
    timer2->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
    timer2->control_reg_b |= CONF_CONTROL_REG_B_FPWM;

    /* determinar la frecuencia con el registro OCR2A */
    timer2->compare_reg_a = TIMER2_FREQ_L;

    /* determinar el ancho de la senal en alto en cada ciclo con el registro OCR2B */
    timer2->compare_reg_b = MAX_PWM_8P;

    /* reiniciar el registro del contador (por las dudas) */
    timer2->counter_reg = 0;

    return 0;
}

int timer2_motor(int speed)
{
    long int init_value, temp;
    uint8_t low, high;

    // if (speed < 0 || speed > 180)
    //     return 1;

    init_value = speed * 100 / 180;
    temp = MIN_PWM_8P + (MAX_PWM_8P_MOTOR - MIN_PWM_8P) / 100 * init_value;
    high = (temp >> 8);
    low = temp;

    /*

    /* determinamos el ancho de la señal en alto en cada ciclo con el registro OCR2B */
    timer2->compare_reg_b = low;

    return 0;
}