/*
 * ringbuffer.c
 *
 * Created: 3/24/2013 1:09:52 AM
 *  Author: Peter
 */ 

#include "ringbuffer.h"
#include "interrupts.h"

int ringTop;
int ringBottom;
int currentMetal;
int currentRefl;
item ringBuf[RING_BUF_SIZE];
int bufLength;
char inPause;
char shutdown;

int totalSorted;
int whiteSorted;
int blackSorted;
int steelSorted;
int aluminumSorted;

/* void initRingBuf()
   Purpose: initializes the ring buffer
   */
void initRingBuf() {
	ringTop = 0;
	ringBottom = 0;
	currentMetal = -1;
	currentRefl = 0;
	bufLength = 0;
	inPause = 0;
	shutdown = 0;
	
	totalSorted = 0;
	whiteSorted = 0;
	blackSorted = 0;
	steelSorted = 0;
	aluminumSorted = 0;
}

/* int newRingBufItem()
   Purpose: adds an item to the ring buffer and returns its index
   */
int newRingBufItem() {
	// this next line is for cases when queue is not empty
	if(bufLength > 0) {
		ringBottom = getBufOffset(ringBottom, 1);
	}		
	bufLength++;
	ringBuf[ringBottom].minRefl = 1024;
	ringBuf[ringBottom].reflSamples = 0;
	ringBuf[ringBottom].metal = 0;
	ringBuf[ringBottom].type = UNDEF;
	return ringBottom;
}

/* void popBuf()
   Purpose: pops the top item off the buffer
   */
void popBuf() {
	// if the buffer is empty, break
	if (bufLength == 0) return;
	// case for length is 1
	if(bufLength == 1) {
		bufLength--;
	} else {
		ringTop = getBufOffset(ringTop, 1);
		bufLength--;
	}	
	if((bufLength == 0) && (shutdown == 1)) {
		shutdownHandler();
	}
}

/* int getBufOffset(int index, int offset)
   Purpose: gets the index which is an integer offset of the given
   index.
   */
int getBufOffset(int index, int offset) {
	// case for wrapping around top end
	if((index + offset) > (RING_BUF_SIZE - 1)) {
		return ((index + offset) - RING_BUF_SIZE);
	}
	// case for wrapping around bottom end
	if((index + offset) < 0) {
		return ((index + offset) + RING_BUF_SIZE);
	}

	// didn't wrap
	return (index + offset);
}