/*

MUST Be INCLUDED IN Main Program 
Scheduler.startLoop(runMotorLoop);

Motors.runMotorLoop();

*/


#include "Arduino.h"
#include "Motors.h"

Motors::Motors(int nothing) {
AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
float leftSpeed;
float rightSpeed;
}

//Definition of Movement related functions
long Motors::cmToSteps(float cm)
{
  return (long)((cm * 1600.0)/(6.46 * 3.14159265358979));
}

boolean Motors::motorsRunning() {
  if (leftMotor.distanceToGo() != 0 || rightMotor.distanceToGo() != 0) {
    return true;
  }
  else {
    return false;
  }
}

void Motors::straight(float cm) {
  leftMotor.move(cmToSteps(cm));
  rightMotor.move(-cmToSteps(cm));
}

void Motors::rotate(float deg) {//positive rotates Right, negative rotates Left
  leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75)); //Note that 13.99 is the 'diameter' that gives the most accurate movement for a 360 rotate
  rightMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75));
}

void Motors::swingWithRight (float deg) { //Positive turns LEFT!!!  Negative turns RIGHT!!! (going backwards)
  leftMotor.move(0);
  rightMotor.move(-cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void Motors::swingWithLeft(float deg) {//Positive turns Right, Negative turns Left (going backwards)
  rightMotor.move(0);
  leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void Motors::setMotorSpeeds() {
  if (leftSpeed > 0) {
    leftMotor.move(1000000);
    leftMotor.setSpeed(leftSpeed);
  }
  else if (leftSpeed < 0) {
    leftMotor.move(-1000000);
    leftMotor.setSpeed(leftSpeed);
  }
  else {
    leftMotor.move(0);
    leftMotor.setSpeed(0);
  }
  
  if (rightSpeed > 0) {
    rightMotor.move(-1000000);
    rightMotor.setSpeed(-rightSpeed);
  }
  else if (rightSpeed < 0) {
    rightMotor.move(1000000);
    rightMotor.setSpeed(-rightSpeed);
  }
  else {
    rightMotor.move(0);
    rightMotor.setSpeed(0);
  }
}

void Motors::setup()
{
  leftMotor.setMaxSpeed(900);
  rightMotor.setMaxSpeed(900);
  leftMotor.setAcceleration(10000);
  rightMotor.setAcceleration(10000);

  leftMotor.setSpeed(leftSpeed);//Must be set once to allow movement, setSpeed(float) should be called after moveTo, not needed to be called after move()
  rightMotor.setSpeed(rightSpeed);//Must be set once to allow movement
}

void Motors::runMotorLoop() {
  leftMotor.run();
  rightMotor.run();  
  yield();
}