/*
 * interrupts.h
 *
 * Created: 3/23/2013 2:05:17 PM
 *  Author: Peter
 */ 


#define STEEL_MAX 800
#define STEEL_MIN 100
#define ALUMINUM_MAX 100
#define ALUMINUM_MIN 30
#define BLACK_MAX 1000
#define BLACK_MIN 925
#define WHITE_MAX 915
#define WHITE_MIN 840
#define REFL_MIN_SAMPLES 1
#define DEBOUNCE_DELAY_US 250
#define DEBOUNCE_SAMPLES 8
#define BUTTON_DEBOUNCE_DELAY 20

void vectorInterrupts();
void makeDecision(int index);
void exitHandler();
void shutdownHandler();
void pausedHandler();

/*ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);
ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);*/