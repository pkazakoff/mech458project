/*
 * interrupts.h
 *
 * Created: 3/23/2013 2:05:17 PM
 *  Author: Peter
 */ 

#define STEEL_MAX 255
#define STEEL_MIN 0
#define ALUMINUM_MAX 255
#define ALUMINUM_MIN 0
#define BLACK_MAX 255
#define BLACK_MIN 0
#define WHITE_MAX 255
#define WHITE_MIN 0
#define REFL_MIN_SAMPLES 0

void vectorInterrupts();
void makeDecision(int index);

/*ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);
ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);*/