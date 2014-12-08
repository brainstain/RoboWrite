#include "RoboWrite.h"

RoboWrite::RoboWrite(AccelStepper& stepper1, AccelStepper& stepper2, Servo myservo,long wheelDiameter, long width) :
_stepper1(stepper1), _stepper2(stepper2)
{
	_BACKWARD = -1;
	_FORWARD = 1;
	_circumference = wheelDiameter * 3.14;
	WIDTH = width;
	SPEED = 1000;
	DELAY = 2000;
	pos = 60;
	_myservo = myservo;
}

void RoboWrite::forward(long inches) {

  int steps = -(inches * 2055) / _circumference ;
  step(steps, -steps);
}

void RoboWrite::reverse(long inches) {
  forward(-inches);
}

void RoboWrite::turnLeftArc(long theta){
  
  int steps = 2 * theta * WIDTH * 3.14 * 2055 / (_circumference * 360);
  step(-steps, 0);
}

void RoboWrite::turnRightArc(long theta){
   int steps = 2 * theta * WIDTH * 3.14 * 2055 / (_circumference * 360);
  step(0, -steps); 
}

void RoboWrite::turnLeftPoint(long theta){
  int steps = 2 * theta * WIDTH * 3.14 * 2055 / (_circumference * 360);
  step(-steps, steps);
}

void RoboWrite::turnRightPoint(long theta) {
  turnLeftPoint(-theta);
}

void RoboWrite::penUp() {
  for(; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                 // in steps of 1 degree 
    _myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  } 
  pos = 60;
  _myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

void RoboWrite::penDown() {
  for(; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    _myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  }
  pos = 0;
  _myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

void RoboWrite::step(long lsteps, long rsteps){ // 2000, 1000
  int dirL = (lsteps > 0) ? _BACKWARD : _FORWARD;
  int dirR = (rsteps > 0) ? _BACKWARD : _FORWARD;
  lsteps = abs(lsteps);
  rsteps = abs(rsteps);
  if (lsteps >= rsteps) {
    double offset = 0;
    if (rsteps > 0) {
      double delta = double(lsteps - rsteps) / rsteps;  // 3
      for ( ; rsteps > 0; ) {
        offset += delta;
        stepOne(dirL, dirR, SPEED);
        lsteps--;
        rsteps--;
        for(; offset >= 1; offset--) {  // 3 * 0 | 3 * 1
          stepOneLeft(dirL, SPEED);
          lsteps--;
        }
      }
    }
    for(; lsteps > 0; lsteps--) {
      stepOneLeft(dirL, SPEED);
    }
  } else {
    double offset = 0;
    if (lsteps > 0) {
      double delta = double(rsteps - lsteps) / lsteps;
      for ( ; lsteps > 0; ) {
        offset += delta;
        stepOneLeft(dirL, SPEED);
        lsteps--;
        rsteps--;
        for(; offset >= 1; offset--) {  // 3 * 0 | 3 * 1
          stepOneRight(dirR, SPEED);
          rsteps--;
        }
      }
    }
    for(; rsteps > 0; rsteps--) {
      stepOneRight(dirR, SPEED);
    }
  }
}

void RoboWrite::stepOne(int dirL, int dirR, float speed) {
//  Serial.print("\nstepOne");
  _stepper1.move(dirR*1);
  _stepper1.setSpeed(speed);
  _stepper1.runSpeedToPosition();
  delayMicroseconds(DELAY); 
  _stepper2.move(dirL*-1);
  _stepper2.setSpeed(speed);
  _stepper2.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}

void RoboWrite::stepOneLeft(int dirL, float speed) {
//  Serial.print("\nstepOneLeft");
  _stepper2.move(dirL*-1);
  _stepper2.setSpeed(speed);
  _stepper2.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}

void RoboWrite::stepOneRight(int dirR, float speed) {
//  Serial.print("\nstepOneRight");
  _stepper1.move(dirR);
  _stepper1.setSpeed(speed);
  _stepper1.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}