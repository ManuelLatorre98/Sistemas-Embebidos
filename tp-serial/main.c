/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "knight_rider.h"
#include "ultrasound.h"
#include "globals.h"
int main(void)
{   
    /* Configure the UART for the serial driver */
    serial_init();
    serial_put_string("EJECUTANDO\n");
    while (1)
    {
        // Wait for an incoming character 
        rcvChar = serial_get_char();

        // Echo the character back along with a carriage return and line feed 
        //serial_put_char(rcvChar);
        //serial_put_char('\r');
        //serial_put_char('\n');
        if(rcvChar == 'k'){
            knight_rider_run();
        }else if(rcvChar == 'u'){
            ultrasound_run();
        }
    }

    for (;;);
    return 0;
}

