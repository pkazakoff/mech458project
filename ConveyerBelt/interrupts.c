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
	if(ringBuf[index].reflSamples < REFL_MIN_SAMPLES) return; // TODO: goes to error
	char refl = ringBuf[index].avgRefl;
	if((refl < STEEL_MAX) && (refl > STEEL_MIN)) {
		ringBuf[index].type = STEEL;
	}
	if((refl < ALUMINUM_MAX) && (refl > ALUMINUM_MIN)) {
		ringBuf[index].type = ALUMINUM;
	}
	if((refl < BLACK_MAX) && (refl > BLACK_MIN)) {
		ringBuf[index].type = BLACK;
	}
	if((refl < WHITE_MAX) && (refl > WHITE_MIN)) {
		ringBuf[index].type = WHITE;
	}
	// TODO: jumps to error if gets here
}

/* void firstLaserHandler()
   Purpose: handler for the first laser
   */
void firstLaserHandler() {
	currentMetal = newRingBufItem();
}

/* void metalHandler()
   Purpose: handler for the inductive sensor
   */
void metalHandler() {
	ringBuf[currentMetal].metal = 1;
}

/* void secondLaserHandler()
   Purpose: on RE completes the inductive stage and starts
   the reflectivity stage.
   on FE completes the reflective stage */
void secondLaserHandler() {
	if(ADC_is_running == 1) {
		// stop ADC
		stopADC();
		makeDecision(currentRefl);
		// TODO
	} else {
		currentRefl = currentMetal;
		startADC();
	}
}

/* void exitHandler()
   Purpose: handles the exit sensor
   */
void exitHandler() {
	// TODO
}

/* ISR(INT0_vect)
   Purpose: Falling-edge interrupt vector
   for FIRST LASER
   */
ISR(INT0_vect){
	writeDecInt(0);
	firstLaserHandler();
}

/* ISR(INT1_vect)
   Purpose: Falling-edge interrupt vector
   for INDUCTIVE SENSOR
   */
ISR(INT1_vect){
	writeDecInt(1);
	metalHandler();
}

/* ISR(INT2_vect)
   Purpose: Rising and falling-edge interrupt
   vector for SECOND LASER
   */
ISR(INT2_vect){
	secondLaserHandler();
	writeDecInt(2);
}

/* ISR(INT3_vect)
   Purpose: Falling-edge interrupt vector
   for EXIT SENSOR
   */
ISR(INT3_vect) {
	exitHandler();
	writeDecInt(3);
}

/* ISR(INT4_vect)
   Purpose: Falling-edge interrupt vector
   for HALL EFFECT SENSOR
   */
ISR(INT4_vect) {
	hallLow = 1;
	writeDecInt(4);
}

/* ISR(INT5_vect)
   Purpose: Falling-edge interrupt vector
   for BUTTON 2
   */
ISR(INT5_vect) {
	writeDecInt(5);
}

/* ISR(INT6_vect)
   Purpose: Falling-edge interrupt vector
   for BUTTON 1
   */
ISR(INT6_vect){
	writeDecInt(6);
}