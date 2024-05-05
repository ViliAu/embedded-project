/*
 * buzzer.c
 *
 * Created: 7.4.2024 13.26.30
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 * Sources : ATmega328p datasheet pp. 111-159, course exercise 7
 */ 

#include "buzzer.h"

static bool g_setup = false;

/* functions for the timer/counter1 compare match A interrupt vector */
ISR
(TIMER1_COMPA_vect)
{
	TCNT1 = 0; // reset timer counter
}

// Course exercise 7 code used
void setup_buzzer() {
	if (g_setup == false) {
		// disable global interrupts while writing to the registers (specifically TCNT1)
		// (see ATmega datasheet p. 114)
		cli();
		// set OC1A to output (digital pin 9)
		DDRB |= (1 << PB1);
		// set up the 16-bit timer/counter1, mode 9 used
		TCCR1B  = 0;
		TCNT1   = 0;
		// set compare output mode to toggle
		TCCR1A |= (1 << 6);
		// mode 9 phase correct
		TCCR1A |= (1 << 0); // set register A WGM[1:0] bits
		TCCR1B |= (1 << 4); // set register B WBM[3:2] bits
		TIMSK1 |= (1 << 1); // enable compare match A interrupt
		
		OCR1A = 15297; // C5 523 Hz, no prescaler
		// enable global interrupts
		sei();
		g_setup = true;
	}
}

void disable_buzzer() {
	/* disable timer/counter1 */
	TCCR1B &= ~(1 << 0);
}

void enable_buzzer() {
	setup_buzzer();
	/* enable timer/counter1 */
	TCCR1B |= (1 << 0); // set prescaling to 1 (no prescaling)
}
