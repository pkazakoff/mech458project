/*
 * adc.c
 *
 * Created: 3/24/2013 3:39:06 PM
 *  Author: Peter
 */ 

#include "adc.h"
#include "ringbuffer.h"
#include <avr/interrupt.h>
#include "SevenSegmentDisplay.h"
#include "interrupts.h"

char ADC_is_running;
char Ignore_ADC_samples;

void setupADC() {
	DDRF = 0x00;
	// ADC setup
	ADCSRA |= _BV(ADEN);
	ADCSRA |= _BV(ADIE);
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	ADMUX |= _BV(REFS0) | 0b01;
	ADC_is_running = 0;
	Ignore_ADC_samples = 0;
	sei();
}

void startADC() {
	ADC_is_running = 1;
	ADCSRA |= _BV(ADSC);
	sei();
}

void stopADC() {
	ADC_is_running = 0;
	ADCSRA &= ~_BV(ADSC);
}

void updateMinimum(int refl) {
	// are we to ignore samples?
	if(Ignore_ADC_samples == 1) return;
	// if we have too many samples, toss 'em
	if(ringBuf[currentRefl].reflSamples >= REFL_MAX_SAMPLES) return;
	// throw out spurious values
	if((refl < REFL_MIN) || (refl > REFL_MAX)) return;
	// average it out
	/* OLD AVERAGE METHOD, prone to overflow at high clock */
	/*long int meanprod = (long)ringBuf[currentRefl].avgRefl * (long)ringBuf[currentRefl].reflSamples;
	meanprod += refl;
	ringBuf[currentRefl].reflSamples++;
	ringBuf[currentRefl].avgRefl = meanprod / ringBuf[currentRefl].reflSamples;
	delaynms(1);*/
	if(ringBuf[currentRefl].minRefl > refl) ringBuf[currentRefl].minRefl = refl;
	ringBuf[currentRefl].reflSamples++;
	return;
}

ISR(ADC_vect) {
	updateMinimum(ADC);
	ADCSRA |= _BV(ADSC);
}