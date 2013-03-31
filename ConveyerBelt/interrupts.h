/*
 * interrupts.h
 *
 * Created: 3/23/2013 2:05:17 PM
 *  Author: Peter
 */ 

#define STEEL_MAX 0x250
#define STEEL_MIN 0x1CC
#define ALUMINUM_MAX 0x050
#define ALUMINUM_MIN 0x03F
#define BLACK_MAX 0x2F7
#define BLACK_MIN 0x2EA
#define WHITE_MAX 0x2E9
#define WHITE_MIN 0x2CF
#define REFL_MIN_SAMPLES 5

void vectorInterrupts();
void makeDecision(int index);
void exitHandler();

/*ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
ISR(INT3_vect);
ISR(INT4_vect);
ISR(INT5_vect);
ISR(INT6_vect);*/