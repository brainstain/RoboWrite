#ifndef RoboWrite_h
#define RoboWrite_h

#include <AccelStepper.h>
#include <Servo.h>
#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif
#undef round
class RoboWrite 
{
public:
	RoboWrite(AccelStepper stepper1, AccelStepper stepper2, Servo myservo, long wheelDiameter, long width);
	void forward(long inches);
	void reverse(long inches);
	void turnLeftArc(long theta);
	void turnRightArc(long theta);
	void turnLeftPoint(long theta);
	void turnRightPoint(long theta);
	void penUp();
	void penDown();
private:
	void step(long lsteps, long rsteps);
	void stepOne(int dirL, int dirR, float speed);
	void stepOneLeft(int dirL, float speed);
	void stepOneRight(int dirR, float speed);
	int SPEED;
	int DELAY;
	int _BACKWARD;
	int _FORWARD;
	long WIDTH;
	Servo _myservo;
	int pos;
	float _circumference;
	AccelStepper _stepper1;
	AccelStepper _stepper2;
};

#endif 