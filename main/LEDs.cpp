/* 
 * Filename: LEDs.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 02/22/2021
 * File Purpose: interfacing with RGB LEDs
 */


#include "Arduino.h"


// write the specified RGB color to the specified LED
void write_RGB(int red_pin, int green_pin, int blue_pin, 
               int red_value, int green_value, int blue_value)
{
  analogWrite(red_pin, red_value);
  analogWrite(blue_pin, green_value);
  analogWrite(green_pin, blue_value); 
}