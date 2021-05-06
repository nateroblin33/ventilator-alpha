/* 
 * Filename: LEDs.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 05/06/2021
 * File Purpose: interfacing with RGB LEDs
 */


#include "Arduino.h"


// write the specified RGB color to the specified LED
void write_RGB(int red_pin, int green_pin, int blue_pin, int rgb[])
{
  analogWrite(red_pin, rgb[0]);
  analogWrite(blue_pin, rgb[1]);
  analogWrite(green_pin, rgb[2]); 
}
