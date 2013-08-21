#ifndef Motors_h
#define Motors_h

#include "Arduino.h"

class Motors
{
  public:
    AccelStepper leftMotor(AccelStepper::DRIVER, 7, 6);
    AccelStepper rightMotor(AccelStepper::DRIVER, 5, 4);
    float leftSpeed;
    float rightSpeed;
    void straight(float cm);
    void rotate(float deg);
    void swingWithRight (float deg);
    void swingWithLeft(float deg);
    void setMotorSpeeds();
    void setup();
    void runMotorLoop();
    boolean motorsRunning();
  private:
    long cmToSteps(float cm);
};

#endif