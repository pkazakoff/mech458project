/*
 * SevenSegnmentDisplay.h
 * Purpose: Function Prototypes for 7-segment display driver
 * Created: 3/23/2013 1:43:05 PM
 *  Author: Peter
 */ 

char getPatFomHex(char number);
void writePattern(char pattern);
void writeDecInt(int number);
void writeHexInt(int number);