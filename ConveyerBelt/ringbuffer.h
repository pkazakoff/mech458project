/*
 * ringbuffer.h
 *
 * Created: 3/24/2013 1:10:04 AM
 *  Author: Peter
 */

// Number of elements in ring buffer
#define RING_BUF_SIZE 64

// Structure definition for buffer element
typedef struct {
	char type;
	char metal;
	char avgRefl;
	int reflSamples;
} item;

// Make global variables accessible to all
// source files which include this header
extern int ringTop;
extern int ringBottom;
extern item ringBuf[RING_BUF_SIZE];

// function prototypes
void initRingBuf();
int newRingBufItem();
void popBuf();
int getBufOffset(int index, int offset);