/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "prueba.h"

int main(void)
{   
    /*volatile unsigned char * DDR_B = (unsigned char *) 0x24;
    volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
    (*DDR_B)=0b00010000;
    (*PUERTO_B) = 0b00100000;*/
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    /*serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');*/

    while (1)
    {
        
        
        // Wait for an incoming character 
        rcvChar = serial_get_char();

        // Echo the character back along with a carriage return and line feed 
        serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n');
        if(rcvChar == 'e'){
            prender();
        }else if('a'){
            apagar();
        }
        

    }

    for (;;);
    return 0;
}

