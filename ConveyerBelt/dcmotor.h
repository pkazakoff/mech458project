/*
 * dcmotor.h
 *
 * Created: 3/26/2013 2:16:23 PM
 *  Author: Peter
 */ 

#define MOTOR_DEF_SPEED 0x9F
#define MOTOR_BITMASK 0xF0
#define MOTOR_FWD_PATTERN 0b00001000
#define MOTOR_REV_PATTERN 0b00000001
#define MOTOR_BRAKE_PATTERN 0b00000000
#define MOTOR_COAST_PATTERN 0b00000110

// motor FSM
typedef enum motorStates {
	BRAKE,
	FORWARD,
	REVERSE,
	COAST
} motorStates;


extern motorStates motorState;
extern motorStates pausedMotorState;
extern char motorWaitForStepper;
extern char pausedForUndef;

void setupMotor();
void setMotorSpeed(char speed);
void setMotorFwd();
void setMotorRev();
void setMotorBrake();
void setMotorCoast();