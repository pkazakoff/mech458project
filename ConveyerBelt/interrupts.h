/*
 * interrupts.h
 *
 * Created: 3/23/2013 2:05:17 PM
 *  Author: Peter
 */ 

#define STEEL_MAX 550
#define STEEL_MIN 340
#define ALUMINUM_MAX 300
#define ALUMINUM_MIN 5
#define BLACK_MAX 680
#define BLACK_MIN 640
#define WHITE_MAX 638
#define WHITE_MIN 600
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