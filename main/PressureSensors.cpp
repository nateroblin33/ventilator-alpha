/* 
 * Filename: PressureSensors.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 02/22/2021
 * File Purpose: interfacing with pressure sensors
 */


 #include "Arduino.h"


// convert voltage to pressure value
float convert_pressure(int v)
{
  float offset = 200.0;
  float sensitivity = 4.413;
  float adc_mv = 4.8828125;

  float mmh20_kpa = 0.00981;
  
  return (v * adc_mv - offset) / sensitivity * mmh20_kpa;
}


// retrieve voltage values of sensor, converting to pressure
float read_pressure(int pin)
{
  return convert_pressure(analogRead(pin));
}
