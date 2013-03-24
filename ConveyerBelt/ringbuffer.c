/*
 * ringbuffer.c
 *
 * Created: 3/24/2013 1:09:52 AM
 *  Author: Peter
 */ 

#include "ringbuffer.h"

int ringTop
int ringBottom;
item ringBuf[RING_BUF_SIZE];

/* void initRingBuf()
   Purpose: initializes the ring buffer
   */
void initRingBuf() {
	ringTop = 0;
	ringBottom = 0;
}

/* int newRingBufItem()
   Purpose: adds an item to the ring buffer and returns its index
   */
int newRingBufItem() {
	ringBottom = getBufOffset(ringBottom, 1);
	ringBuf[ringBottom].avgRefl = 0;
	ringBuf[ringBottom].reflSamples = 0;
	ringBuf[ringBottom].metal = 0;
	ringBuf[ringBottom].type = 0;
	return ringBottom;
}

/* void popBuf()
   Purpose: pops the top item off the buffer
   */
void popBuf() {
	// if the buffer is empty, break
	if ((ringBottom - ringTop) = 0) break;
	ringTop = getBufOffset(ringTop, 1);
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
		return ((index + offset) + RING_BUF_SIZE)
	}
	// didn't wrap
	return (index + offset);
}