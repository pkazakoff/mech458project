/*
 * CFile1.c
 *
 * Created: 3/24/2013 12:49:04 PM
 *  Author: Blake Abercrombie
 */

// Define steps of bins from 0 
#define BLACK_POSITION 0
#define	ALUMINUM_POSIITION 50
#define WHITE_POSITION 150
#define STEEL_POSITION 200

extern char hallLow;
extern int steps;

void initalizeStepper();
void stepTime(int n, char d);
void stepperMoveTo(int p);