/*
 * adc.h
 *
 * Created: 3/24/2013 3:39:26 PM
 *  Author: Peter
 */ 

#define REFL_MIN 50
#define REFL_MAX 1024
#define REFL_MAX_SAMPLES 200

extern char ADC_is_running;
extern char Ignore_ADC_samples;

void setupADC();
void startADC();
void stopADC();