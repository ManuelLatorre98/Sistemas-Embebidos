#include "globals.h"

volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
//volatile unsigned int seconds=0;
volatile int servo_angles[N_SERVOS]={0,0,0,0};
volatile int servo_ticks[N_SERVOS]={0,0,0,0};
