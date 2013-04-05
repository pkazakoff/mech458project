/*
 * SevenSegmentDisplay.c
 *
 * Created: 3/22/2013 6:16:15 PM
 *  Author: Peter
 */ 

#include <avr/io.h>
#include "timer.h"
#include "SevenSegmentDisplay.h"

#define DISPLAY_DIGITS 5

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

/* void writeError(int code)
   Purpose: displays "ErrXX" on the 
   display, where XX is the hex representation of the integer
   */
void writeError(int code) {
	// write the error code
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(code % 16));
		code = code / 16;
	}
	// write "r"
	writePattern(0b00001010);
	// write "r"
	writePattern(0b00001010);
	// write "E"
	writePattern(0b10011110);
}

/* void writeTotal(int count)
   Purpose: displays "totXX" on the 
   display, where XX is the decimal
   representation of the integer
   */
void writeTotal(int count) {
	// write the count
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(count % 10));
		count = count / 10;
	}
	// write "t"
	writePattern(0b00011110);
	// write "o"
	writePattern(0b00111010);
	// write "t"
	writePattern(0b00011110);
}


/* void writeAluminum(int count)
   Purpose: displays "ALUXX" on the 
   display, where XX is the decimal
   representation of the integer
   */
void writeAluminum(int count) {
	// write the count
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(count % 10));
		count = count / 10;
	}
	// write "U"
	writePattern(0b01111100);
	// write "L"
	writePattern(0b00011100);
	// write "A"
	writePattern(0b11101110);
}

/* void writeSteel(int count)
   Purpose: displays "StLXX" on the 
   display, where XX is the decimal
   representation of the integer
   */
void writeSteel(int count) {
	// write the count
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(count % 10));
		count = count / 10;
	}
	// write "L"
	writePattern(0b00011100);
	// write "t"
	writePattern(0b00011110);
	// write "S"
	writePattern(0b10110110);
}

/* void writeBlack(int count)
   Purpose: displays "bLAXX" on the 
   display, where XX is the decimal
   representation of the integer
   */
void writeBlack(int count) {
	// write the count
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(count % 10));
		count = count / 10;
	}
	// write "A"
	writePattern(0b11101110);
	// write "L"
	writePattern(0b00011100);
	// write "b"
	writePattern(0b00111110);
}

/* void writeWhite(int count)
   Purpose: displays "LtEXX" on the 
   display, where XX is the decimal
   representation of the integer
   */
void writeWhite(int count) {
	// write the count
	for (int i=0; i < 2; i++) {
		writePattern(getPatFomHex(count % 10));
		count = count / 10;
	}
	// write "E"
	writePattern(0b10011110);
	// write "t"
	writePattern(0b00011110);
	// write "L"
	writePattern(0b00011100);
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