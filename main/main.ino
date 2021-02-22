/* 
 * Filename: main.ino
 * Author: Kyle Bannerman
 * Date Created: 02/19/2021
 * Date of Last Edit: 02/19/2021
 * File Purpose: main controller of arduino
 */


#include "_init.h"
#include "PressureSensors.h"
#include "Buttons.h"
#include "LEDs.h"


// init main
void setup() 
{
  
  // init pressure alert RGB LED pins
  pinMode(PRESS_R_PIN, OUTPUT);
  pinMode(PRESS_G_PIN, OUTPUT);
  pinMode(PRESS_B_PIN, OUTPUT);

  // init battery alert RGB LED pins
  pinMode(BATT_R_PIN, OUTPUT);
  pinMode(BATT_G_PIN, OUTPUT);
  pinMode(BATT_B_PIN, OUTPUT);

  // init default setting button pins
  pinMode(DEF0_BUT_PIN, INPUT);
  pinMode(DEF1_BUT_PIN, INPUT);
  pinMode(DEF2_BUT_PIN, INPUT);
}


void loop() 
{
    
  // read in pressure sensor values
  int input_pressure = read_pressure(PRESS_I_PIN);
  int output_pressure = read_pressure(PRESS_O_PIN);

  // check for default setting button pressure
  int default_selected = -1;
  if (read_button(DEF0_BUT_PIN)) default_selected = 0;
  else if (read_button(DEF1_BUT_PIN)) default_selected = 1;
  else if (read_button(DEF2_BUT_PIN)) default_selected = 2;

  // write to battery status LEDs
  write_RGB(BATT_R_PIN, BATT_G_PIN, BATT_B_PIN, 0, 255, 0);

  // write to pressure status LEDs
  write_RGB(PRESS_R_PIN, PRESS_G_PIN, PRESS_B_PIN, 0, 255, 0);
  
}
