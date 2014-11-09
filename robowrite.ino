#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"



// BEGIN STEPPER DECLS

/*-----( Import needed libraries )-----*/
#include <AccelStepper.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define FULLSTEP 4
#define HALFSTEP 8
// motor pins
#define motorPin1  A0     // Blue   - 28BYJ48 pin 1
#define motorPin2  A1     // Pink   - 28BYJ48 pin 2
#define motorPin3  A2     // Yellow - 28BYJ48 pin 3
#define motorPin4  A3     // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
                        
#define motorPin5  6    // Blue   - 28BYJ48 pin 1
#define motorPin6  7     // Pink   - 28BYJ48 pin 2
#define motorPin7  8    // Yellow - 28BYJ48 pin 3
#define motorPin8  9    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
/*-----( Declare objects )-----*/
// NOTE: The sequence 1-3-2-4 is required for proper sequencing of 28BYJ48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper2(FULLSTEP, motorPin5, motorPin7, motorPin6, motorPin8);

#define BACKWARD -1
#define FORWARD 1

// END STEPPER DECLS


// BEGIN SERVO DECLS

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 60;    // variable to store the servo position 

// END SERVO DECLS

/**************************************************************************/
/*!
    @brief  Sets up the HW and the CC3000 module (called automatically
            on startup)
*/
/**************************************************************************/



const float CALIBRATE = 2.910;  // The original DR10's calibration


void setup(void)
{
  Serial.begin(115200);
  // INIT STEPPERS

  stepper1.setMaxSpeed(1500.0);
  stepper2.setMaxSpeed(1500.0);

  myservo.attach(4);  // attaches the servo on pin 2 to the servo object 
  penUp();

  Serial.println(F("Hello, CC3000!\n"));
  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);
}

long hex2int(char *a, int len)
{
    int i;
    long val = 0;
    for(i=0;i<len;i++) {
       if(a[i] <= 57)
        val += (a[i]-'0')*(1<<(4*(len-1-i)));
       else
        val += (a[i]-'A'+10)*(1<<(4*(len-1-i)));
    }
    return val;
}

void loop() {

  //runArduino();
  //forward(6);
  hackNash();
}

void hackNash(){
  penDown();
  forward(8);
  penUp();
  reverse(4);
  turnRightPoint(90);
  penDown();
  forward(3);
  penUp();
  turnLeftPoint(90);
  forward(4);
  penDown();
  reverse(8);
  penUp();
  turnRightPoint(90);
  forward(1);
  turnLeftPoint(75);
  penDown();
  forward(8.3);
  turnRightPoint(150);
  forward(8.3);
  penUp();
  turnLeftPoint(75);
  forward(4);
  turnLeftPoint(180);
  penDown();
  turnRightArc(90);
  forward(2.8);
  turnRightArc(90);
  penUp();
  forward(1);
  turnRightPoint(90);
  penDown();
  forward(8);
  penUp();
  reverse(4);
  turnLeftPoint(30);
  penDown();
  forward(4.6);
  penUp();
  reverse(4.6);
  turnLeftPoint(120);
  penDown();
  forward(4.8);
  penUp();
  turnRightPoint(60);
  forward(3.8);
  turnLeftPoint(180);
  penDown();
  turnLeftArc(90);
  forward(2.8);
  turnLeftArc(360);
  penUp();
  forward(2.6);
  turnRightPoint(90);
  forward(16);
  turnLeftPoint(90);
  forward(5);
  penDown();
  forward(4);
  penUp();
  reverse(4);
  turnLeftPoint(30);
  penDown();
  forward(4.6);
  turnRightPoint(30);
  reverse(4);
  penUp();
  turnLeftPoint(90);
  forward(1);
  turnRightPoint(90);
  forward(4);
  turnRightPoint(15);
  penDown();
  reverse(4.14);
  turnLeftPoint(30);
  forward(4.14);
  penUp();
  turnLeftPoint(75);
  forward(1);
  penDown();
  forward(2.6);
  turnLeftArc(180);
  turnRightArc(180);
  forward(2.6);
  penUp();
  forward(1);
  turnRightPoint(90);
  forward(1.2);
  penDown();
  forward(4);
  penUp();
  reverse(2);
  turnLeftPoint(90);
  penDown();
  forward(2);
  penUp();
  turnLeftPoint(90);
  forward(2);
  penDown();
  reverse(4);
  penUp();
  delay(5000);
}

void runArduino(){
  penDown();
  turnLeftArc(270);
  forward(5.2);
  turnRightArc(270);
  forward(5.2);
  penUp();
  turnLeftPoint(90);
  forward(3.1);
  turnRightPoint(45);
  forward(1);
  turnLeftPoint(185);
  penDown();
  forward(2);
  penUp();
  forward(7.35);
  turnRightPoint(180);
  penDown();
  forward(2);
  penUp();
  turnRightPoint(135);
  forward(2.1);
  turnRightPoint(135);
  penDown();
  forward(2);
  penUp();
  delay(5000);
}

#define WHEELDIAMETER 1.77
#define WIDTH  5.2

const float circumference = WHEELDIAMETER * 3.14;
void forward(long inches) {

  int steps = -(inches * 2055) / circumference ;
  step(steps, steps);
}

void reverse(long inches) {
  forward(-inches);
}

void turnLeftArc(long theta){
  
  int steps = 2 * theta * WIDTH * 3.14 * 2055 / (circumference * 360);
  step(-steps, 0);
}

void turnRightArc(long theta){
   int steps = 2 * theta * WIDTH * 3.14 * 2055 / (circumference * 360);
  step(0, -steps); 
}

void turnLeftPoint(long theta){
  int steps = theta * WIDTH * 3.14 * 2055 / (circumference * 360);
  step(-steps, steps);
}

void turnRightPoint(long theta) {
  turnLeftPoint(-theta);
}

void penUp() {
  for(; pos < 60; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                 // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  } 
  pos = 60;
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

void penDown() {
  for(; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
                      // waits 15ms for the servo to reach the position 
  }
  pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos' 
}

#define SPEED 1000

void step(long lsteps, long rsteps){ // 2000, 1000
  int dirL = (lsteps > 0) ? BACKWARD : FORWARD;
  int dirR = (rsteps > 0) ? BACKWARD : FORWARD;
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

#define DELAY 2000  // This appears to be the minimum delay (3ms) to allow the motors to complete one step

void stepOne(int dirL, int dirR, float speed) {
//  Serial.print("\nstepOne");
  stepper1.move(dirR*1);
  stepper1.setSpeed(speed);
  stepper1.runSpeedToPosition();
  delayMicroseconds(DELAY); 
  stepper2.move(dirL*-1);
  stepper2.setSpeed(speed);
  stepper2.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}

void stepOneLeft(int dirL, float speed) {
//  Serial.print("\nstepOneLeft");
  stepper2.move(dirL*-1);
  stepper2.setSpeed(speed);
  stepper2.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}

void stepOneRight(int dirR, float speed) {
//  Serial.print("\nstepOneRight");
  stepper1.move(dirR);
  stepper1.setSpeed(speed);
  stepper1.runSpeedToPosition();
  delayMicroseconds(DELAY); 
}
