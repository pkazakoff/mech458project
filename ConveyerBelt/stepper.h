/*
 * CFile1.c
 *
 * Created: 3/24/2013 12:49:04 PM
 *  Author: Blake Abercrombie
 */

// Define steps of bins from 0 
#define BLACK_POSITION 0
#define	ALUMINUM_POSIITION 50
#define WHITE_POSITION 100
#define STEEL_POSITION 150

#define STEP_BASE_SPEED 15
#define ACCEL_INTERVAL 2
#define MODIFIER_LOWER_LIMIT 0
#define MODIFIER_UPPER_LIMIT 0
#define KNEE_NUMERATOR 7
#define KNEE_DENOMINATOR 8

extern char hallLow;
extern int steps;

void initalizeStepper();
void stepTime(int n, char d);
void stepperMoveTo(int p);
int forwardSteps(int current, int target);
int reverseSteps(int current, int target);
