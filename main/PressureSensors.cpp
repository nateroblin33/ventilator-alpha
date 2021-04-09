/* 
 * Filename: PressureSensors.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 04/09/2021
 * File Purpose: interfacing with pressure sensors
 */


 #include "Arduino.h"


// convert voltage to pressure value
float convert_pressure(int v)
{
  float offset = 2.6103;
  float slope = 0.0827;
  
  return v * adc_mv - offset;
}


// retrieve voltage values of sensor, converting to pressure
float read_pressure(int pin)
{
  return convert_pressure(analogRead(pin));
}
