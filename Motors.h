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
    void setMotorSpeeds(float leftSpeed, float rightSpeed);
    void setup();
    void runMotorLoop();
    boolean motorsRunning();
  private:
    long cmToSteps(float cm);
	float _leftSpeed;
    float _rightSpeed;
	AccelStepper _leftMotor;
    AccelStepper _rightMotor;
};

#endif