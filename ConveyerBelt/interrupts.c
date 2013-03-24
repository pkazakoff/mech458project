/*
 * interrupts.c
 *
 * Created: 3/23/2013 2:05:09 PM
 *  Author: Peter
 */ 

#include <avr/io.h>
#include "interrupts.h"
#include "SevenSegmentDisplay.h"
#include <avr/interrupt.h>

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


/* ISR(INT0_vect)
   Purpose: Falling-edge interrupt vector
   for FIRST LASER
   */
ISR(INT0_vect){
	writeDecInt(0);
}

/* ISR(INT1_vect)
   Purpose: Falling-edge interrupt vector
   for INDUCTIVE SENSOR
   */
ISR(INT1_vect){
	writeDecInt(1);
}

/* ISR(INT2_vect)
   Purpose: Rising and falling-edge interrupt
   vector for SECOND LASER
   */
ISR(INT2_vect){
	writeDecInt(2);
}

/* ISR(INT3_vect)
   Purpose: Falling-edge interrupt vector
   for EXIT SENSOR
   */
ISR(INT3_vect) {
	writeDecInt(3);
}

/* ISR(INT4_vect)
   Purpose: Falling-edge interrupt vector
   for HALL EFFECT SENSOR
   */
ISR(INT4_vect) {
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