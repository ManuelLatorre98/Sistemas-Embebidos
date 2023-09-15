#include "globals.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
volatile unsigned int seconds=0;
volatile int servo_angles[4]; //Array que contiene los ticks necesarios por los servos