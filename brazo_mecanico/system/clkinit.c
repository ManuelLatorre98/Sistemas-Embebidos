/* clkinit.c */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

uint32	clktime;		/* Seconds since boot			*/
unsigned long  count1000;	/* ms since last clock tick             */
qid16	sleepq;			/* Queue of sleeping processes		*/
unsigned long preempt;		/* Preemption counter			*/

/*------------------------------------------------------------------------
 * clkinit  -  Initialize the clock and sleep queue at startup
 *------------------------------------------------------------------------
 */
void clkinit(void)
{
	
	struct clock_csreg * clockptr;

	sleepq = newqueue();	/* Allocate a queue to hold the delta	*/
				/*   list of sleeping processes		*/
	preempt = QUANTUM;	/* Set the preemption time		*/
	clktime = 0;		/* Start counting seconds		*/
        count1000 = 0;


	/* 
         * AVR atmega328p timer/clock init: interrupt every 1ms 
	 * The AVR TIMER interrupt rutine is in clkhandler.c
         */
// RAFA
/*
	TCCR0B |= (1<<CS01) | (1<<CS00);   //clock select is divided by 64.
	TCCR0A |= (1<<WGM01);              //sets mode to CTC

	#if ATMEGA
		OCR0A = 0xF9;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	#else
		OCR0A = 63;                      //sets TOP to 124 so the timer will overflow every 1 ms.    
	#endif
	TIMSK0 |= (1<<OCIE0A);              //Output Compare Match A Interrupt Enable
*/

  // NORMAL MODE
  TCCR2A = (1<<COM2A1) | (0<<COM2A0) | (0<<COM2B1)| (0<<COM2B0) | (0<<3) | (0<<2) | (0<<WGM21) | (0<<WGM20);  

// Cada dos milisegundos
  TCCR2B = (0<<FOC2A) | (0<<FOC2B) | (0<<5) | (0<<4) | (0<<WGM22) | (1<<CS22) | (0<<CS21) | (1<<CS20); 
  
  // Activo Timer2 Overflow Interrupt
  TIMSK2 =(0<<7) | (0<<6) | (0<<5) | (0<<4) | (0<<3) | (0<<OCIE2B) | (0<<OCIE2A) | (1<<TOIE2);  
  
  // Oscilador interno
  ASSR = (0<<7) | (0<<EXCLK) | (0<<AS2) | (0<<TCN2UB) | (0<<OCR2AUB) | (0<<OCR2BUB) | (0<<TCR2AUB) | (0<<TCR2BUB) ;
  
  //Activo interrupciones globales.
//  sei();

	return;
}

