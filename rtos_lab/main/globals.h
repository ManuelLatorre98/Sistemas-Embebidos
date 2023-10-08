#ifndef GLOBALS_H
#define GLOBALS_H
#define N_SERVOS 4
extern volatile unsigned char * DDR_B;
extern volatile unsigned char * PUERTO_B;
extern volatile unsigned char * PIN_B;
extern volatile unsigned  int seconds;
extern volatile int servo_angles[N_SERVOS]; //Array que contiene los ticks necesarios por los servos
volatile int servo_ticks[N_SERVOS]; //Array que contiene los angulos necesarios por los servos
#endif