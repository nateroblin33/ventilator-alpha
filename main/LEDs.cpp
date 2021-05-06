/* 
 * Filename: LEDs.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 04/30/2021
 * File Purpose: interfacing with RGB LEDs
 */


#include "Arduino.h"


// write the specified RGB color to the specified LED
void write_RGB(int red_pin, int green_pin, int blue_pin, 
               int red_value, int green_value, int blue_value)
{
  analogWrite(red_pin, red_value);
  analogWrite(blue_pin, blue_value);
  analogWrite(green_pin, green_value); 
}
