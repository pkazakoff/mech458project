/*
 * interrupts.c
 *
 * Created: 3/23/2013 2:05:09 PM
 *  Author: Peter
 */ 

#include <avr/io.h>
#include "interrupts.h"
#include "SevenSegmentDisplay.h"
#include "ringbuffer.h"
#include <avr/interrupt.h>
#include "adc.h"
#include "stepper.h"
#include "dcmotor.h"
#include "timer.h"
#include "metalqueue.h"

/* void vectorInterrupts()
   Purpose: sets the interrupt registers to enable
   external interrupts on the desired pins
   */
void vectorInterrupts() {
	
	// disable external interrupts temporarily
	EIMSK &= 0b10000000;
	
	// Set all interrupt pins to input
	DDRD = DDRD & 0xF0;
	DDRE = DDRE & 0x0F;
	
	// INT0 - First Laser
	// Falling-edge interrupt
	EICRA |= _BV(ISC01);
	EICRA &= ~(_BV(ISC00));
	
	// INT1 - Metal Detector
	// Falling-edge interrupt
	EICRA |= _BV(ISC11);
	EICRA &= ~(_BV(ISC10));
	
	// INT2 - Second Laser
	// Rising and falling edge interrupt
	EICRA &= ~(_BV(ISC21));
	EICRA |= _BV(ISC20);
	
	// INT3 - Exit Sensor
	// Falling-edge interrupt
	EICRA |= _BV(ISC31);
	EICRA &= ~(_BV(ISC30));	
	
	// INT4 - Hall-effect sensor
	// Falling-edge interrupt
	EICRB |= _BV(ISC41);
	EICRB &= ~(_BV(ISC40));
	
	// INT5 - Button2
	// Falling-edge interrupt
	EICRB |= _BV(ISC51);
	EICRB &= ~(_BV(ISC50));
	
	// INT6 - Button1
	// Falling-edge interrupt
	EICRB |= _BV(ISC61);
	EICRB &= ~(_BV(ISC60));
	
	
	// Enable interrupts
	EIMSK |= 0b01111111;
	EIFR |= 0b01111111;
	sei();
}

void makeDecision(int index) {
	//if(ringBuf[index].reflSamples < REFL_MIN_SAMPLES) return; // TODO: goes to error
	//writeHexInt(ringBuf[index].avgRefl);
	int refl = ringBuf[index].minRefl;
	if(ringBuf[index].metal == 1) {
		if((refl < STEEL_MAX) && (refl > STEEL_MIN)) {
			ringBuf[index].type = STEEL;
			return;
		}
		if((refl < ALUMINUM_MAX) && (refl > ALUMINUM_MIN)) {
			ringBuf[index].type = ALUMINUM;
			return;
		}
	} else {	
		if((refl < BLACK_MAX) && (refl > BLACK_MIN)) {
			ringBuf[index].type = BLACK;
			return;
		}
		if((refl < WHITE_MAX) && (refl > WHITE_MIN)) {
			ringBuf[index].type = WHITE;
			return;
		}
	}
	writeHexInt(0xEF);	
	return;
}

/* void firstLaserHandler()
   Purpose: handler for the first laser
   */
void firstLaserHandler() {
	// no pending item
	if(currentMetal == -1) {
		currentMetal = newRingBufItem();
	} else {
		//item in conversion
		
		// place the currently converting item on the queue
		newMetal(currentMetal);
		
		// make the new item and start conversion
		currentMetal = newRingBufItem();
	}
}

/* void metalHandler()
   Purpose: handler for the inductive sensor
   */
void metalHandler() {
	if(currentMetal != -1) ringBuf[currentMetal].metal = 1;
}

/* void secondLaserHandler()
   Purpose: on RE completes the inductive stage and starts
   the reflectivity stage.
   on FE completes the reflective stage */
void secondLaserHandler() {
	if(ADC_is_running == 1) {
		// debounce
		Ignore_ADC_samples = 1;
		delaynms(DEBOUNCE_DELAY);
		Ignore_ADC_samples = 0;
		if((PIND & 0b00000100) == 0b100) return;
		// stop ADC
		stopADC();
		makeDecision(currentRefl);
		// TODO
	} else {
		delaynms(DEBOUNCE_DELAY);
		if((PIND & 0b00000100) == 0) return;
		if(metalCount == 0) {
			currentRefl = currentMetal;
			currentMetal = -1;
		} else {
			currentRefl = popMetal();
		}			
		startADC();
	}
}

/* void exitHandler()
   Purpose: handles the exit sensor
   */
void exitHandler() {
	// is there an item on the queue?
	if(bufLength==0) return;
	// if we're in pause, ignore it as it's probably
	// the operator pulling the piece off
	if(inPause==1) return;
	// are we in position?
	switch(ringBuf[ringTop].type) {
		case BLACK:
			if(steps==BLACK_POSITION) {
				blackSorted++;
				totalSorted++;
				writeBlack(blackSorted);
				popBuf();
				return;
			}
			break;
		case STEEL:
			if(steps==STEEL_POSITION) {
				steelSorted++;
				totalSorted++;
				writeSteel(steelSorted);
				popBuf();
				return;
			}
			break;
		case ALUMINUM:
			if(steps==ALUMINUM_POSIITION) {
				aluminumSorted++;
				totalSorted++;
				writeAluminum(aluminumSorted);
				popBuf();
				return;
			}
			break;
		case WHITE:
			if(steps==WHITE_POSITION) {
				whiteSorted++;
				totalSorted++;
				writeWhite(whiteSorted);
				popBuf();
				return;
			}
			break;
		default:
			//undefined item
			writeError(0xF0);
			pausedForUndef = 1;
			pausedHandler();
			return;
			break;
	}			
	// we got here, so we're not at the correct position yet.
	// stop the motor
	setMotorBrake();
	// set a flag to let the stepper know we're waiting
	motorWaitForStepper = 1;
}

void shutdownHandler() {
	if(bufLength == 0) {
		delaynms(500);
		setMotorBrake();
		while(1);
	}
}

void pausedHandler() {
	if(inPause == 1) {
		inPause = 0;
		// restore the motor state
		switch (pausedMotorState) {
			case FORWARD:
				setMotorFwd();
				break;
			case REVERSE:
				setMotorRev();
				break;
			case BRAKE:
				setMotorBrake();
				break;
			case COAST:
				setMotorCoast();
				break;
			default:
				break;
		}
		// see if the last item was undefined
		if(pausedForUndef) {
			popBuf();
		}
	} else {
		// store the motor state
		pausedMotorState = motorState;
		setMotorBrake();
		inPause = 1;
	}
}

/* ISR(INT0_vect)
   Purpose: Falling-edge interrupt vector
   for FIRST LASER
   */
ISR(INT0_vect){
	delaynms(DEBOUNCE_DELAY);
	if((PIND & 0b1) == 0) firstLaserHandler();
}

/* ISR(INT1_vect)
   Purpose: Falling-edge interrupt vector
   for INDUCTIVE SENSOR
   */
ISR(INT1_vect){
	delaynms(DEBOUNCE_DELAY);
	if((PIND & (1 << 1)) == 0) metalHandler();
}

/* ISR(INT2_vect)
   Purpose: Rising and falling-edge interrupt
   vector for SECOND LASER
   */
ISR(INT2_vect){
	// debounce is handled by function call
	secondLaserHandler();
}

/* ISR(INT3_vect)
   Purpose: Falling-edge interrupt vector
   for EXIT SENSOR
   */
ISR(INT3_vect) {
	delaynms(DEBOUNCE_DELAY);
	if((PIND & (1 << 3)) == 0) exitHandler();
}

/* ISR(INT4_vect)
   Purpose: Falling-edge interrupt vector
   for HALL EFFECT SENSOR
   */
ISR(INT4_vect) {
	delaynms(DEBOUNCE_DELAY);
	if((PINE & (1 << 4)) == 0) hallLow = 1;
}

/* ISR(INT5_vect)
   Purpose: Falling-edge interrupt vector
   for BUTTON 2
   */
ISR(INT5_vect) {
	delaynms(BUTTON_DEBOUNCE_DELAY);
	if((PINE & (1 << 5)) == 0) {
		shutdown = 1;
		shutdownHandler();
	}
}

/* ISR(INT6_vect)
   Purpose: Falling-edge interrupt vector
   for BUTTON 1
   */
ISR(INT6_vect){
	delaynms(BUTTON_DEBOUNCE_DELAY);
	if((PINE & (1 << 6)) == 0) {
		pausedHandler();
	}
}