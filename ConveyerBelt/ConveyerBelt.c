/*
 * ConveyerBelt.c
 *
 * Created: 3/22/2013 11:10:43 PM
 *  Author: Peter
 */ 


#include <avr/io.h>
#include "timer.h"
#include "SevenSegmentDisplay.h"
#include "interrupts.h"

int main(void)
{
	// Set the dev board's clock speed to the external oscillator with
	// no prescaler (8MHz)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;
	
	// Initialize hardware timer
	initializeTimer();
	
	// enable output
	DDRA = 0xFF;
	
	// vector interrupts
	//vectorInterrupts();
	
    while(1)
    {
		for(int i=60; i > 0; i--) {
			writeDecInt(i);
			delaynms(1000);
		}
		writeHexInt(0xB00);
		delaynms(2000);	
        //TODO:: Please write your application code 
    }
}