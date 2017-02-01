/*
*  A simple stepper class for the 28byj-48 stepper and tillhörande driver.
*
*  Author: Albin Winkelmann
*    Date: 15.12.2016 - 00:36
*/

#include "Arduino.h"
#include "Stepper28byj48.h"

Stepper28byj48::Stepper28byj48(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
  IN1 = pin1;
  IN2 = pin2;
  IN3 = pin3;
  IN4 = pin4;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  direction = true;
  steps = 0;
  stepsLeft = 0;

}
void Stepper28byj48::setDirection(){
  if(direction==1){ steps++;}
  if(direction==0){ steps--; }
  if(steps>7){steps=0;}
  if(steps<0){steps=7;}
}

void Stepper28byj48::stepper(int xw){
  for (int x=0;x<xw;x++){
    switch(steps){
       case 0:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break;
       case 1:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break;
       case 2:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break;
       case 3:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break;
       case 4:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break;
       case 5:
         digitalWrite(IN1, HIGH);
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break;
         case 6:
         digitalWrite(IN1, HIGH);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break;
       case 7:
         digitalWrite(IN1, HIGH);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break;
       default:
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break;
     }
    setDirection();
    }
  }

void Stepper28byj48::resetStepper() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Stepper28byj48::runStepper(int degree) {
  long calculateSteps = 4095 / 360;
  calculateSteps *= degree;
  stepsLeft = calculateSteps;
  while(stepsLeft > 0){
    currentMillis = micros();
    if(currentMillis - lastTime >= 1000){
      stepper(1);
      lastTime = micros();
      stepsLeft--;
    }
  }
  resetStepper();
}

void Stepper28byj48::runStepper() {
  stepsLeft = 4095;
  while(stepsLeft > 0){
    currentMillis = micros();
    if(currentMillis - lastTime >= 1000){
      stepper(1);
      lastTime = micros();
      stepsLeft--;
    }
  }
  resetStepper();
  Serial.println("Turned one cycle");
}

void Stepper28byj48::turnClockwise(int degree) {
  direction = true;
  runStepper(degree);
}

void Stepper28byj48::turnClockwise() {
  direction = true;
  runStepper();
}

void Stepper28byj48::turnAntiClockwise(int degree) {
  direction = false;
  runStepper(degree);
}

void Stepper28byj48::turnAntiClockwise() {
  direction = false;
  runStepper();
}
