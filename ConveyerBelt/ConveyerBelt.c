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
	
	/*stepperMoveTo(STEEL_POSITION);
	delaynms(4000);
	stepperMoveTo(BLACK_POSITION);
	delaynms(4000);
	stepperMoveTo(ALUMINUM_POSIITION);
	delaynms(4000);
	stepperMoveTo(STEEL_POSITION);
	setMotorBrake();
	while(1);*/

	while(1) {
		// check the next item off the conveyer belt, rotate to the correct position
		if(bufLength > 0) {
			switch(ringBuf[ringTop].type) {
				case BLACK:
					stepperMoveTo(BLACK_POSITION);
					delaynms(500);
					break;
				case WHITE:
					stepperMoveTo(WHITE_POSITION);
					delaynms(500);
					break;
				case STEEL:
					stepperMoveTo(STEEL_POSITION);
					delaynms(500);
					break;
				case ALUMINUM:
					stepperMoveTo(ALUMINUM_POSIITION);
					delaynms(500);
					break;
				default:
					break;
			}
		}
	}
	
}