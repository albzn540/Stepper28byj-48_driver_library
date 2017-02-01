/*
*  A simple stepper class for the 28byj-48 stepper and tillhörande driver.
*
*  Author: Albin Winkelmann
*    Date: 15.12.2016 - 00:36
*/

#ifndef Stepper28byj48_h
#define Stepper28byj48_h

#include "Arduino.h"

class Stepper28byj48 {
public:
  Stepper28byj48(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
  void turnClockwise(int degree);
  void turnAntiClockwise(int degree);
  void turnClockwise();
  void turnAntiClockwise();

private:
  uint8_t IN1;
  uint8_t IN2;
  uint8_t IN3;
  uint8_t IN4;
  boolean direction;
  int steps;
  int stepsLeft;
  unsigned long lastTime;
  unsigned long currentMillis;
  long time;

  void resetStepper();
  void stepper(int xw);
  void runStepper(int degree);
  void runStepper();
  void setDirection();
};

#endif
