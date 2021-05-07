/* 
 * Filename: main.ino
 * Author: Kyle Bannerman
 * Date Created: 02/19/2021
 * Date of Last Edit: 05/06/2021
 * File Purpose: main controller of arduino
 */


#include "_init.h"
#include "PressureSensors.h"
#include "Buttons.h"
#include "LEDs.h"
#include "LCDScreen.h"
#include "MotorControl.h"


// user defined constants
#define PRESSURE_MAX 100
#define PRESSURE_MIN 0


// RGB quantifiers for the LEDs
int top_RGB[3] = {255, 0, 0};
int bot_RGB[3] = {255, 0, 0};


// mode and default setting selected
int mode_sel = 0;
int def_sel = 0;
int mot_speed = 350;


// switch the operating mode
void switch_mode()
{
  mode_sel = mode_sel ^ 1;

  // update LED indicator if switch occurs
  if (mode_sel == 0) 
  {
    top_RGB[0] = 255;
    top_RGB[1] = 0;
    top_RGB[2] = 0;
  }
  else
  {
    top_RGB[0] = 0;
    top_RGB[1] = 0;
    top_RGB[2] = 255;
  }
}


// init main
void setup() 
{

  Serial.begin(9600);
  
  // init bottom RGB LED pins
  pinMode(BOT_R_PIN, OUTPUT);
  pinMode(BOT_G_PIN, OUTPUT);
  pinMode(BOT_B_PIN, OUTPUT);

  // init top RGB LED pins
  pinMode(TOP_R_PIN, OUTPUT);
  pinMode(TOP_G_PIN, OUTPUT);
  pinMode(TOP_B_PIN, OUTPUT);

  // init default setting button pins
  pinMode(DEF0_BUT_PIN, INPUT);
  pinMode(DEF1_BUT_PIN, INPUT);
  pinMode(DEF2_BUT_PIN, INPUT);

  // init LCD screen
  init_screen();

  // set the max speed of the motor
  set_max();
  
}


// operation loop
void loop() 
{
  // write to the LEDs
  write_RGB(TOP_R_PIN, TOP_G_PIN, TOP_B_PIN, top_RGB);
  write_RGB(BOT_R_PIN, BOT_G_PIN, BOT_B_PIN, bot_RGB);

  // check for default setting button pressure
  if (read_button(DEF0_BUT_PIN)) 
  {
    def_sel = 0;
    mot_speed = 350;
  }
  else if (read_button(DEF1_BUT_PIN))
  {
    def_sel = 1;
    mot_speed = 400;
  }
  else if (read_button(DEF2_BUT_PIN))
  {
    def_sel = 2;
    mot_speed = 450;
  }
  
  // check for mode switch
  if (read_button(MODE_BUT_PIN)) switch_mode();
  
//  // read potentiometer
//  float pot_val = analogRead(POT_PIN);

  // write to LCD screen
  write_pressure_vals(1.0, 1.1);
  
  // move motor forwards
//  run_mot_forward(mot_speed);
//
//  // move motor backwards
//  run_mot_backward(mot_speed);

}
