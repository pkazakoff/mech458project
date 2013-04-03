/*
 * metalqueue.c
 *
 * Created: 4/2/2013 11:43:53 AM
 *  Author: Peter
 */ 

#include "metalqueue.h"

int metalQueue[METAL_QUEUE_SIZE];

int metalTop;
int metalBottom;
int metalCount;

/* void initMetalQueue()
   Purpose: initializes the ring buffer
   */
void initMetalQueue() {
	metalTop = 0;
	metalBottom = 0;
	metalCount = 0;
	metalQueue[metalTop] = 0;
}

/* int newMetal()
   Purpose: adds an item to the ring buffer and returns its index
   */
int newMetal(int content) {
	// if bottom is lagging behind top, reset bottom
	if(metalCount==0) metalBottom = metalTop;
	// this next line is for cases when queue is not empty
	if(metalCount > 0) metalBottom = getMetalOffset(metalBottom, 1);
	metalCount++;
	metalQueue[metalBottom] = content;
	return metalBottom;
}

/* void popMetal()
   Purpose: pops the top item off the buffer
   */
int popMetal() {
	// if the buffer is empty, break
	if (metalCount == 0) return -1;
	int content = metalQueue[metalTop];
	metalTop = getMetalOffset(metalTop, 1);
	metalCount--;
	return content;
}

/* int getBufOffset(int index, int offset)
   Purpose: gets the index which is an integer offset of the given
   index.
   */
int getMetalOffset(int index, int offset) {
	// case for wrapping around top end
	if((index + offset) > (METAL_QUEUE_SIZE - 1)) {
		return ((index + offset) - METAL_QUEUE_SIZE);
	}
	// case for wrapping around bottom end
	if((index + offset) < 0) {
		return ((index + offset) + METAL_QUEUE_SIZE);
	}

	// didn't wrap
	return (index + offset);
}