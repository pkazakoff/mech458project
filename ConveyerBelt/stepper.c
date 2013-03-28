/*
 * stepper.c
 *
 * Created: 3/24/2013 12:53:15 PM
 *  Author: Blake Abercrombie
 */ 

#include "stepper.h"
#include "timer.h"
#include <avr/io.h>


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
	PORTA = PORTA & (0b11000000|states[currentState]);
	hallLow = 0;
}


void stepTime(int stepTime, char direction) {
	delaynms(stepTime);
	if(direction == 0) { //forward direction
		currentState++;
		if (currentState==4) currentState = 0;
		PORTA = PORTA & (0b11000000 | states[currentState]);
		steps++;
		if(hallLow = 1) {
			steps = 0;
			hallLow = 0;
		}
	}
	else { //reverse direction
		currentState--;
		if (currentState==-1) currentState = 3;
		PORTA = PORTA & (0b11000000 | states[currentState]);
		steps--;
		if(hallLow = 1) {
			steps = 0;
			hallLow = 0;
		}				
	}
}

// function to calculate how stepper should rotate
void stepperMoveTo(int nextPosition){
	char direction;
	// calculate what direction stepper should turn
	if(nextPosition > steps) direction = 0;
	else direction = 1;
	// calculate how many steps to move
	int stepsRequired = abs(nextPosition-steps); 
	// rotate stepper
	for(int i=0; i<stepsRequired; i++){
		stepTime(15,direction);
	}
}	


