/* 
 * Filename: MotorControl.cpp
 * Author: Kyle Bannerman
 * Date Created: 05/06/2021
 * Date of Last Edit: 05/06/2021
 * File Purpose: nonblocking control of the motor
 */


#include <TimeLib.h>
#include <AccelStepper.h>


// user defined constants
#define PRESS_I_PIN 0

#define MAX_SPEED 500
#define OP_SPEED 450
#define EXTENSION_POS 330
#define ORIGIN_POS 0


// init stepper control
AccelStepper stepper(AccelStepper::FULL4WIRE, 8, 9, 10, 11); 


// set the max speed for the motor
void set_max() 
{
  stepper.setMaxSpeed(MAX_SPEED);    
}


// run motor in the forwards direction
void run_mot_forward(int mot_speed)
{ 
  // forwards movement
  stepper.setSpeed(mot_speed);
  while (stepper.currentPosition() != EXTENSION_POS) 
  {
    delay(3);
    stepper.runSpeed();
  }
}


// run the motor in the reverse direction
void run_mot_backward(int mot_speed)
{
  // backwards return
  stepper.setSpeed(-mot_speed);
  while (stepper.currentPosition() != ORIGIN_POS) stepper.runSpeed();
}
