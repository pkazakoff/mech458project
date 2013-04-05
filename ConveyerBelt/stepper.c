/*
 * stepper.c
 *
 * Created: 3/24/2013 12:53:15 PM
 *  Author: Blake Abercrombie
 */ 

#include "stepper.h"
#include "timer.h"
#include "dcmotor.h"
#include "interrupts.h"
#include <avr/io.h>
#include "SevenSegmentDisplay.h"
#include <stdlib.h>


// possible states
const char states[] = {48, 6, 40, 5};
// track current state
int currentState;
// track steps from 0
int steps;
// variable for when hall effect sensor goes low
char hallLow;


// set initial values for stepper
void initalizeStepper() {
	// enable output
	DDRA |= 0b00111111;
	currentState = 0;
	PORTA = (PORTA & 0b11000000) | states[currentState];
	hallLow = 0;
	steps = 1;
}


void stepTime(int stepTime, char direction) {
	delaynms(stepTime);
	if(direction == 0) { //forward direction
		currentState++;
		if (currentState==4) currentState = 0;
		PORTA = (PORTA & 0b11000000) | states[currentState];
		steps++;
		if(hallLow == 1) {
			steps = 0;
			hallLow = 0;
		}
	}
	else { //reverse direction
		currentState--;
		if (currentState==-1) currentState = 3;
		PORTA = (PORTA & 0b11000000) | states[currentState];
		steps--;
		if(steps < 0) steps = 199;
		if(hallLow == 1) {
			steps = 0;
			hallLow = 0;
		}				
	}
}

// function to calculate how stepper should rotate
void stepperMoveTo(int nextPosition){
	if (steps == nextPosition) return;
	if(forwardSteps(steps, nextPosition) < reverseSteps(steps, nextPosition)) {
		while(steps != nextPosition) {
			stepTime(15,0);
		}
	}
	
	else {
			while(steps != nextPosition) {
				stepTime(15,1);
			}			
		}
	
	if(motorWaitForStepper == 1) {
		// start the motor back up
		setMotorFwd();
		// clear the flag
		motorWaitForStepper = 0;
		// fire the exit logic again
		exitHandler();
	}
}




int forwardSteps(int current, int target) {
	int stepsRequired;
	
	// no wrap around
	if(target > current) stepsRequired = abs(target - current);
	
	// wrap arround
	else stepsRequired = abs(200 - abs(target - current));
	
	return stepsRequired;
}

int reverseSteps(int current, int target) {
	int stepsRequired;
	
	// wrap around
	if(target < current) stepsRequired = abs(target - current);

	// no wrap around
	else stepsRequired = abs(200 - abs(target - current));
	
	return stepsRequired;
}

