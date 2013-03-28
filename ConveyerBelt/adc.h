/*
 * adc.h
 *
 * Created: 3/24/2013 3:39:26 PM
 *  Author: Peter
 */ 

#define REFL_MIN 200
#define REFL_MAX 255
#define REFL_MAX_SAMPLES 300

extern char ADC_is_running;

void setupADC();
void startADC();
void stopADC();