/*
 * tarea_led: este programa parpadea el led de la placa.
 * 
 * Se desarrolla como un programa aislado del resto.
 */

#include <xinu.h>


int led_placa(void)
{
    volatile unsigned char* DDR_B = (unsigned char*) 0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*) 0x25;

    *DDR_B = 0x20; // control: salida.

    while (1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001; //on
        
    }

}

