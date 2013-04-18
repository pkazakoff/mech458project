/*
 * metalqueue.h
 *
 * Created: 4/2/2013 11:44:10 AM
 *  Author: Peter
 */ 

#define METAL_QUEUE_SIZE 100

extern int metalQueue[];
extern int metalTop;
extern int metalBottom;
extern int metalCount;

void initMetalQueue();
int newMetal(int content);
int popMetal();
int getMetalOffset();