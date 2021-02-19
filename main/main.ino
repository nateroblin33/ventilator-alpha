/* 
 * Filename: main.ino
 * Author: Kyle Bannerman
 * Date Created: 02/19/2021
 * Date of Last Edit: 02/19/2021
 * File Purpose: main controller of arduino
 */


#include "_init.h"


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


void loop() {}
