/* 
 * Filename: main.ino
 * Author: Kyle Bannerman
 * Date Created: 04/12/2021
 * Date of Last Edit: 04/18/2021
 * File Purpose: main controller of arduino
 */
 
// include the Arduino Stepper Library
#include <Stepper.h>

// number of steps per output rotation
const int STEPS_PER_REV = 200;

// create instance of stepper library
Stepper myStepper(STEPS_PER_REV, 8, 9, 10, 11);

// maximum allowed instantaneous flow rate
const float MAX_INST_FLOW = 2.0;

// array of flow rates 
const int FLOWRATES_SIZE = 8;
const float flowRates[FLOWRATES_SIZE] = { 6.75, 6.5, 6.25, 6.0, 5.75, 5.5, 5.25, 5.0 };

// calculate speed necessary to produce desired flow rate -- based on experimental values
float calcSpeed(float flowRate)
{
  return 34.8423 * flowRate - 94.9821;
}

// calculate instantaneous flow rate from speed -- based on experimental values
float calcInstFlowRate(float speedEst)
{
  return 0.0165 * speedEst - 0.617;
}

// check if the instantaneous flow rate exceeds the maximum allowed -- true if safe, false otherwise
bool checkSpeed(float speedEst)
{
  return calcInstFlowRate(speedEst) <= MAX_INST_FLOW;
}


void setup()
{
  Serial.begin(9600);
}

void loop() 
{
  float speedEst;
  for (int i = 0; i < FLOWRATES_SIZE; i++)
  {
    speedEst = calcSpeed(flowRates[i]);

    if (checkSpeend(speedEst))
    {
      myStepper.setSpeed(speedEst);
    
      for (int j = 0; j < 5; j++)
      {
        myStepper.step(STEPS_PER_REV);
      
        delay(500);
      
        myStepper.step(-STEPS_PER_REV);
        
        delay(500);
      } 
    }
    
    delay(5000);
  }
}
