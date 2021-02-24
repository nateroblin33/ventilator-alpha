/* 
 * Filename: main.ino
 * Author: Kyle Bannerman
 * Date Created: 02/19/2021
 * Date of Last Edit: 02/23/2021
 * File Purpose: main controller of arduino
 */


#include "_init.h"
#include "PressureSensors.h"
#include "Buttons.h"
#include "LEDs.h"
#include "LCDScreen.h"


// user defined constants
#define PRESSURE_MAX 100
#define PRESSURE_MIN 0


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

  // init LCD screen
  init_screen();
}


void loop() 
{
    
  // read in pressure sensor values
  float input_pressure = read_pressure(PRESS_I_PIN);
  float output_pressure = read_pressure(PRESS_O_PIN);
  
  // adjust pressure warning LED depending on pressure level
  if (input_pressure > PRESSURE_MAX || input_pressure < PRESSURE_MIN) 
    write_RGB(PRESS_R_PIN, PRESS_G_PIN, PRESS_B_PIN, 255, 0, 0); // red if an issue
  else
    write_RGB(PRESS_R_PIN, PRESS_G_PIN, PRESS_B_PIN, 0, 255, 0); // green if no issues

  // write to battery status LEDs
  write_RGB(BATT_R_PIN, BATT_G_PIN, BATT_B_PIN, 0, 255, 0);

  // check for default setting button pressure
  int default_selected = -1;
  if (read_button(DEF0_BUT_PIN)) default_selected = 0;
  else if (read_button(DEF1_BUT_PIN)) default_selected = 1;
  else if (read_button(DEF2_BUT_PIN)) default_selected = 2;

  // write to LCD screen
  clear_screen();
  write_pressure_vals(input_pressure, output_pressure);
}
