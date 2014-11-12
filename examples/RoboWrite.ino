

/*************************************************** 
  This is an example for the Adafruit CC3000 Wifi Breakout & Shield

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this oRoboWrite.pen source code, 
  please support Adafruit and oRoboWrite.pen-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 
 /*
This example does a test of the TCP client capability:
  * Initialization
  * Optional: SSID scan
  * AP connection
  * DHCP printout
  * DNS lookup
  * Optional: Ping
  * Connect to website and print out webpage contents
  * Disconnect
SmartConfig is still beta and kind of works but is not fully vetted!
It might not work on all networks!
*/
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
#include <RoboWrite.h>
// END STEPPER DECLS

// BEGIN SERVO DECLS

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos = 60;    // variable to store the servo position 

RoboWrite RoboWrite(stepper1, stepper2, myservo, 3.4, 5.1);
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
  RoboWrite.penUp();

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
  //RoboWrite.forward(6);
  hackNash();
}

void hackNash(){
  RoboWrite.penDown();
  RoboWrite.forward(8);
  RoboWrite.penUp();
  RoboWrite.reverse(4);
  RoboWrite.turnRightPoint(90);
  RoboWrite.penDown();
  RoboWrite.forward(3);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(90);
  RoboWrite.forward(4);
  RoboWrite.penDown();
  RoboWrite.reverse(8);
  RoboWrite.penUp();
  RoboWrite.turnRightPoint(90);
  RoboWrite.forward(1);
  RoboWrite.turnLeftPoint(75);
  RoboWrite.penDown();
  RoboWrite.forward(8.3);
  RoboWrite.turnRightPoint(150);
  RoboWrite.forward(8.3);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(75);
  RoboWrite.forward(4);
  RoboWrite.turnLeftPoint(180);
  RoboWrite.penDown();
  RoboWrite.turnRightArc(90);
  RoboWrite.forward(2.8);
  RoboWrite.turnRightArc(90);
  RoboWrite.penUp();
  RoboWrite.forward(1);
  RoboWrite.turnRightPoint(90);
  RoboWrite.penDown();
  RoboWrite.forward(8);
  RoboWrite.penUp();
  RoboWrite.reverse(4);
  RoboWrite.turnLeftPoint(30);
  RoboWrite.penDown();
  RoboWrite.forward(4.6);
  RoboWrite.penUp();
  RoboWrite.reverse(4.6);
  RoboWrite.turnLeftPoint(120);
  RoboWrite.penDown();
  RoboWrite.forward(4.8);
  RoboWrite.penUp();
  RoboWrite.turnRightPoint(60);
  RoboWrite.forward(3.8);
  RoboWrite.turnLeftPoint(180);
  RoboWrite.penDown();
  RoboWrite.turnLeftArc(90);
  RoboWrite.forward(2.8);
  RoboWrite.turnLeftArc(360);
  RoboWrite.penUp();
  RoboWrite.forward(2.6);
  RoboWrite.turnRightPoint(90);
  RoboWrite.forward(17);
  RoboWrite.turnLeftPoint(90);
  RoboWrite.forward(3);
  RoboWrite.penDown();
  RoboWrite.forward(4);
  RoboWrite.penUp();
  RoboWrite.reverse(4);
  RoboWrite.turnLeftPoint(30);
  RoboWrite.penDown();
  RoboWrite.forward(4.6);
  RoboWrite.turnRightPoint(30);
  RoboWrite.reverse(4);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(90);
  RoboWrite.forward(1);
  RoboWrite.turnRightPoint(90);
  RoboWrite.forward(4);
  RoboWrite.turnRightPoint(15);
  RoboWrite.penDown();
  RoboWrite.reverse(4.14);
  RoboWrite.turnLeftPoint(30);
  RoboWrite.forward(4.14);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(75);
  RoboWrite.forward(1);
  RoboWrite.penDown();
  RoboWrite.forward(2.6);
  RoboWrite.turnLeftArc(180);
  RoboWrite.turnRightArc(180);
  RoboWrite.forward(2.6);
  RoboWrite.penUp();
  RoboWrite.forward(1);
  RoboWrite.turnRightPoint(90);
  RoboWrite.forward(6.5);
  RoboWrite.penDown();
  RoboWrite.forward(4);
  RoboWrite.penUp();
  RoboWrite.reverse(2);
  RoboWrite.turnLeftPoint(90);
  RoboWrite.penDown();
  RoboWrite.forward(2);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(90);
  RoboWrite.forward(2);
  RoboWrite.penDown();
  RoboWrite.reverse(4);
  RoboWrite.penUp();
  delay(5000);
}

void runArduino(){
  RoboWrite.penDown();
  RoboWrite.turnLeftArc(270);
  RoboWrite.forward(5.2);
  RoboWrite.turnRightArc(270);
  RoboWrite.forward(5.2);
  RoboWrite.penUp();
  RoboWrite.turnLeftPoint(90);
  RoboWrite.forward(3.1);
  RoboWrite.turnRightPoint(45);
  RoboWrite.forward(1);
  RoboWrite.turnLeftPoint(185);
  RoboWrite.penDown();
  RoboWrite.forward(2);
  RoboWrite.penUp();
  RoboWrite.forward(7.35);
  RoboWrite.turnRightPoint(180);
  RoboWrite.penDown();
  RoboWrite.forward(2);
  RoboWrite.penUp();
  RoboWrite.turnRightPoint(135);
  RoboWrite.forward(2.1);
  RoboWrite.turnRightPoint(135);
  RoboWrite.penDown();
  RoboWrite.forward(2);
  RoboWrite.penUp();
  delay(5000);
}

