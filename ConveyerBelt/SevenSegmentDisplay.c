/*
 * SevenSegmentDisplay.c
 *
 * Created: 3/22/2013 6:16:15 PM
 *  Author: Peter
 */ 

#include <avr/io.h>
#include "timer.h"
#include "SevenSegmentDisplay.h"

#define DISPLAY_DIGITS 3

/* char getPatFromHex(char number)
   Purpose: looks up the appropriate pattern for 
   the seven segment display for a given number.
   If input is not between 0-F, returns blank pattern
   */
char getPatFomHex(char number) {
	switch(number) {
		case 0:
			return 0b11111100;
			break;
		case 1:
			return 0b01100000;
			break;
		case 2:
			return 0b11011010;
			break;
		case 3:
			return 0b11110010;
			break;
		case 4:
			return 0b01100110;
			break;
		case 5:
			return 0b10110110;
			break;
		case 6:
			return 0b10111110;
			break;
		case 7:
			return 0b11100000;
			break;
		case 8:
			return 0b11111110;
			break;
		case 9:
			return 0b11100110;
			break;
		case 10:
			return 0b11101110;
			break;
		case 11:
			return 0b00111110;
			break;
		case 12:
			return 0b10011100;
			break;
		case 13:
			return 0b01111010;
			break;
		case 14:
			return 0b10011110;
			break;
		case 15:
			return 0b10001110;
		default:
			break;			
	}
	return 0x00;
}

/* void writePattern(char pattern)
   Purpose: Bit-bangs out an integer over
   the serial interface to the display
   */
void writePattern(char pattern) {
	for (int i=0; i<8; i++) {
		// assert the data
		char databit = 0x01 & (pattern >> i);
		PORTA = (PORTA & 0b10111111) | (databit << 6);
		// rising edge
		PORTA = (PORTA & 0b01111111) | 0b10000000;
		// falling edge
		PORTA = (PORTA & 0b01111111);
	}
}

/* void writeDecInt(int number)
   Purpose: fills the seven segment display with
   an integer number, formatted as decimal.
   */
void writeDecInt(int number) {
	for (int i=0; i < DISPLAY_DIGITS; i++) {
		writePattern(getPatFomHex(number % 10));
		number = number / 10;
	}
}

/* void writeHexInt(int number)
   Purpose: fills the seven segment display with
   an integer number, formatted as hexadecimal.
   */
void writeHexInt(int number) {
	for (int i=0; i < DISPLAY_DIGITS; i++) {
		writePattern(getPatFomHex(number % 16));
		number = number / 16;
	}
}