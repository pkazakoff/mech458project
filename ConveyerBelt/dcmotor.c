/*
 * dcmotor.c
 *
 * Created: 3/26/2013 2:16:07 PM
 *  Author: Peter
 */ 
#include "dcmotor.h"
#include <avr/io.h>

void setupMotor() {
	// enable port for output
	DDRC |= MOTOR_BITMASK;
	
	// put the brakes on
	PORTC = (PORTC & MOTOR_BITMASK) | MOTOR_BRAKE_PATTERN;
	
	// start the PWM output
	
	// enable PWM fast mode
	TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A1) | _BV(COM0B1);
	
	// disable prescaler
	TCCR0B = _BV(CS00);
	
	// set duty cycle
	OCR0A = MOTOR_DEF_SPEED;
}

void setMotorSpeed(char speed) {
	OCR0A = speed;
}

void setMotorFwd() {
	PORTC = (PORTC & MOTOR_BITMASK) | MOTOR_FWD_PATTERN;
}

void setMotorRev() {
	PORTC = (PORTC & MOTOR_BITMASK) | MOTOR_REV_PATTERN;
}

void setMotorCoast() {
	PORTC = PORTC = (PORTC & MOTOR_BITMASK) | MOTOR_COAST_PATTERN;
}