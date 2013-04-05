/*
 * interrupts.h
 *
 * Created: 3/23/2013 2:05:17 PM
 *  Author: Peter
 */ 

#define STEEL_MAX 250
#define STEEL_MIN 56
#define ALUMINUM_MAX 54
#define ALUMINUM_MIN 30
#define BLACK_MAX 520
#define BLACK_MIN 499
#define WHITE_MAX 490
#define WHITE_MIN 440
#define REFL_MIN_SAMPLES 1
#define DEBOUNCE_DELAY 3
#define BUTTON_DEBOUNCE_DELAY 20

void vectorInterrupts();
void makeDecision(int index);
void exitHandler();
void shutdownHandler();

/*ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);
ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);*/