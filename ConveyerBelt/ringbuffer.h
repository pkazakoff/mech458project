/*
 * ringbuffer.h
 *
 * Created: 3/24/2013 1:10:04 AM
 *  Author: Peter
 */

// Number of elements in ring buffer
#define RING_BUF_SIZE 64

// define types
typedef enum itemType {
	UNDEF,
	BLACK,
	WHITE,
	STEEL,
	ALUMINUM
	} itemType;

// Structure definition for buffer element
typedef struct {
	itemType type;
	char metal;
	int minRefl;
	int reflSamples;
} item;

// Make global variables accessible to all
// source files which include this header
extern int ringTop;
extern int ringBottom;
extern int currentMetal;
extern int currentRefl;
extern item ringBuf[];
extern int bufLength;
extern char inPause;
extern char shutdown;

// function prototypes
void initRingBuf();
int newRingBufItem();
void popBuf();
int getBufOffset(int index, int offset);