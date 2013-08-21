/* Fully Functional For controlling 2 Stepper motors on a robot using the Accelstepper library
By Daniel Britten
Released into the public domain
V1.0
*/

/*

MUST Be INCLUDED IN Main Program 
Motors.setup();
Motors.run(); //Must be called regularly

AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);



*/


#include "Arduino.h"
#include "Motors.h"
#include "AccelStepper.h"

Motors::Motors(AccelStepper leftMotor, AccelStepper rightMotor) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
  float _leftSpeed = 500; //default _leftSpeed
  float _rightSpeed = 500; //default _rightSpeed
}

void Motors::setSpeeds (float leftSpeed, float rightSpeed) {
    _leftMotor.setSpeed(leftSpeed);
    _rightMotor.setSpeed(rightSpeed);
  }

void Motors::setAccelerations (float leftAcceleration, float rightAcceleration) {
    _leftMotor.setAcceleration(leftAcceleration);
    _rightMotor.setAcceleration(rightAcceleration);
}

void Motors::setMaxSpeeds (float leftMaxSpeed, float rightMaxSpeed) {
      _leftMotor.setMaxSpeed(leftMaxSpeed);
      _rightMotor.setSpeed(rightMaxSpeed);
	}

//Definition of Movement related functions
long Motors::cmToSteps(float cm)
{
  return (long)((cm * 1600.0)/(6.46 * 3.14159265358979));
}

boolean Motors::running() {
  if (_leftMotor.distanceToGo() != 0 || _rightMotor.distanceToGo() != 0) {
    return true;
  }
  else {
    return false;
  }
}

void Motors::straight(float cm) {
  _leftMotor.move(cmToSteps(cm));
  _rightMotor.move(-cmToSteps(cm));
}

void Motors::rotate(float deg) {//positive rotates Right, negative rotates Left
  _leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75)); //Note that 13.75 is the diameter that gives the most accurate movement for a 360 rotate
  _rightMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75));
}

void Motors::swingWithRight (float deg) { //Positive turns LEFT!!!  Negative turns RIGHT!!! (going backwards)
  _leftMotor.move(0);
  _rightMotor.move(-cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void Motors::swingWithLeft(float deg) {//Positive turns Right, Negative turns Left (going backwards)
  _rightMotor.move(0);
  _leftMotor.move(cmToSteps((deg/360.0)*3.14159265358979*13.75*2));
}

void Motors::setActiveSpeeds(float leftSpeed, float rightSpeed) {
  
  _leftSpeed = leftSpeed;
  _rightSpeed = rightSpeed;
  
  if (_leftSpeed > 0) {
    _leftMotor.move(1000000);
    _leftMotor.setSpeed(_leftSpeed);
  }
  else if (_leftSpeed < 0) {
    _leftMotor.move(-1000000);
    _leftMotor.setSpeed(_leftSpeed);
  }
  else {
    _leftMotor.move(0);
    _leftMotor.setSpeed(0);
  }
  
  if (_rightSpeed > 0) {
    _rightMotor.move(-1000000);
    _rightMotor.setSpeed(-_rightSpeed);
  }
  else if (_rightSpeed < 0) {
    _rightMotor.move(1000000);
    _rightMotor.setSpeed(-_rightSpeed);
  }
  else {
    _rightMotor.move(0);
    _rightMotor.setSpeed(0);
  }
}

void Motors::setup()
{
  _leftMotor.setMaxSpeed(900);
  _rightMotor.setMaxSpeed(900);
  _leftMotor.setAcceleration(10000);
  _rightMotor.setAcceleration(10000);
  _leftMotor.setSpeed(_leftSpeed);//Must be set once to allow movement, setSpeed(float, float) should be called after moveTo, not needed to be called after move()
  _rightMotor.setSpeed(_rightSpeed);//Must be set once to allow movement
}

void Motors::wait() {
  while(running()) yield(); //Should be able to put running() here, but it didn't seem to work...
}

void Motors::run() {
  _leftMotor.run();
  _rightMotor.run();  
}