#include <xinu.h>


int laser_main(void)
{
    volatile unsigned char* DDR_B = (unsigned char*) 0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*) 0x25;
    *(DDR_B)= 0b00000001;//bit 0 = salida
    (*PUERTO_B)= (*PUERTO_B) | 0b00000001;
    while (1){}

}
