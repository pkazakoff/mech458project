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
#include "ringbuffer.h"
#include "adc.h"
#include "stepper.h"
#include "dcmotor.h"
#include "metalqueue.h"

int main(void)
{
	// Set the dev board's clock speed to the external oscillator with
	// no prescaler (8MHz)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0;
	
	// Initialize hardware timer
	initializeTimer();
	
	delaynms(1000);
	
	writeHexInt(0x50);
	
	// Initialize ring buffer
	initRingBuf();
	
	// Initialize metal queue
	initMetalQueue();
	
	writeHexInt(0x51);
	
	// enable output for stepper and display.
	DDRA = 0xFF;

	// vector interrupts
	vectorInterrupts();
	
	writeHexInt(0x52);

	// init stepper
	initalizeStepper();
	
	writeHexInt(0x53);

	// zero stepper
	while(steps != 0){
		stepTime(20,0);
		writeHexInt(steps);
	}
	// set steps from zero to 0 and respective position
	steps = BLACK_POSITION;
	// reset hall effect check
	hallLow = 0;
	

	setupADC();

	// wait one second
	delaynms(1000);
	
	// start the motor
	setupMotor();
	writeHexInt(0x54);
	setMotorFwd();
	
	while(1) {
		// pause if we need to
		while(inPause == 1) {
			writeTotal(totalSorted);
			delaynms(2000);
			if(inPause == 0) break;
			writeWhite(whiteSorted);
			delaynms(2000);
			if(inPause == 0) break;
			writeBlack(blackSorted);
			delaynms(2000);
			if(inPause == 0) break;
			writeSteel(steelSorted);
			delaynms(2000);
			if(inPause == 0) break;
			writeAluminum(aluminumSorted);
			delaynms(2000);
		}
		// check the next item off the conveyer belt, rotate to the correct position
		delaynms(100);
		if(bufLength != 0) {
			switch(ringBuf[ringTop].type) {
				case BLACK:
					stepperMoveTo(BLACK_POSITION);
					break;
				case WHITE:
					stepperMoveTo(WHITE_POSITION);
					break;
				case STEEL:
					stepperMoveTo(STEEL_POSITION);
					break;
				case ALUMINUM:
					stepperMoveTo(ALUMINUM_POSIITION);
					break;
				default:
					break;
			}
		}
	}
	
}