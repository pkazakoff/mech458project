/*
 * timer.c
 *
 * Created: 2/15/2013 2:12:15 PM
 *  Author: Peter Kazakoff & Blake Abercrombie
 */ 
#include "timer.h"
#include <avr/io.h>

void initializeTimer() {
	// bitwise OR to set timer/counter control register
	// to cpu clock, pure timer.
	TCCR1B|=_BV(CS10);
} 

void delaynus(int n)   // delay microseconds
{
	// Set waveform generator bits to 0100 (count up and
	// reset on hit)
	TCCR1B |=_BV(WGM12);
	
	// Set the clock prescaler to 1/64th
	TCCR1B |= 0b00000011;

	// set the output compare register
	// to 1 ms
	OCR1A = n;

	// set initial value to zero
	TCNT1 = 0;

	// enable output compare interrupt enable
	//TIMSK1|=0b00000010;

	// begin timer
	TIFR1|=_BV(OCF1A);

	// poll until we reach our number of milliseconds
	while(1) {
		if((TIFR1 & 0x02) == 0x02) break;
	}
}

void delaynms(int n)   // delay milliseconds
{
	// Set waveform generator bits to 0100 (count up and
	// reset on hit)
	TCCR1B |=_BV(WGM12);
	
	// Set the clock prescaler to 1/64th
	TCCR1B |= 0b00000011;

	for(int i=0; i<n; i++) {
		// set the output compare register
		// to 1 ms
		OCR1A = 125;

		// set initial value to zero
		TCNT1 = 0;

		// enable output compare interrupt enable
		//TIMSK1|=0b00000010;

		// begin timer
		TIFR1|=_BV(OCF1A);

		// poll until we reach our number of milliseconds
		while(1) {
			if((TIFR1 & 0x02) == 0x02) break;
		}
	}	
}