/**********************************************************************
 *
 * Filename:    timer2.h
 *
 * API para la aplicacion embebida
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#ifndef _TIMER2_H
#define _TIMER2_H

int timer2_init();
int timer2_servo(int grade);
int timer2_motor(int speed);
#endif /* _TIMER2_H */