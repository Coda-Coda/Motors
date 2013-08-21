/* Fully Functional For controlling 2 Stepper motors on a robot using the Accelstepper library
By Daniel Britten
Released into the public domain
V1.0
*/

#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include "AccelStepper.h"

class Motors
{
  public:
    Motors(AccelStepper, AccelStepper);
    void straight(float cm);
    void rotate(float deg);
    void swingWithRight (float deg);
    void swingWithLeft(float deg);
    void setActiveSpeeds(float leftSpeed, float rightSpeed);
    void setup();
    void run();
	void wait();
    boolean running();
	void setSpeeds (float leftSpeed, float rightSpeed);
	void setAccelerations (float righttAcceleration, float rightAcceleration);
	void setMaxSpeeds (float leftMaxSpeed, float rightMaxSpeed);
  private:
    long cmToSteps(float cm);
	float _leftSpeed;
    float _rightSpeed;
	AccelStepper _leftMotor;
    AccelStepper _rightMotor;
};

#endif