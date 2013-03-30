/*
 * dcmotor.h
 *
 * Created: 3/26/2013 2:16:23 PM
 *  Author: Peter
 */ 

#define MOTOR_DEF_SPEED 0x7F
#define MOTOR_BITMASK 0x0F
#define MOTOR_FWD_PATTERN 0b00001000
#define MOTOR_REV_PATTERN 0b00000100
#define MOTOR_BRAKE_PATTERN 0b00001100
#define MOTOR_COAST_PATTERN 0b00000011

extern int motorWaitForStepper;

void setupMotor();
void setMotorSpeed(char speed);
void setMotorFwd();
void setMotorRev();
void setMotorBrake();
void setMotorCoast();