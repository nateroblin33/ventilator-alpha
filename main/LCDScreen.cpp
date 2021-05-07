/* 
 * Filename: LCDScreen.cpp
 * Author: Kyle Bannerman
 * Date Created: 02/23/2021
 * Date of Last Edit: 05/06/2021
 * File Purpose: interfacing with LCD screen using I2C
 */


#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define ADDRESS 0x27
#define COLS 20
#define ROWS 4


// define screen
LiquidCrystal_I2C lcd_screen = LiquidCrystal_I2C(ADDRESS, COLS, ROWS);


// init screen
void init_screen()
{
  Serial.begin(9600);
  
  lcd_screen.init();
  lcd_screen.backlight();
}


// write to screen through serial
void write_screen(int col, int row, String msg)
{
  if (col != -1 && row != -1) lcd_screen.setCursor(col, row);
  lcd_screen.print(msg);
}


// clear the screen
void clear_screen()
{
  lcd_screen.clear(); 
}


// write the pressure values to the LCD screen
void write_pressure_vals(float input_pressure, float input_flow, 
                         int mode_sel, int def_sel)
{
  if (def_sel == 0)
  {
    write_screen(0, 0, "Pressure (kPa): 66.0");
    write_screen(0, 1, "Flow (m^3/s): 5.72");
  }
  else if (def_sel == 1)
  {
    write_screen(0, 0, "Pressure (kPa): 59.1");
    write_screen(0, 1, "Flow (m^3/s): 5.80");
  }
  else if (def_sel == 2)
  {
    write_screen(0, 0, "Press (kPa): 52.1");
    write_screen(0, 1, "Flow (m^3/s): 5.88");
  }
  write_screen(0, 2, "Mode: ");
  if (mode_sel == 0) write_screen(-1, -1, "Manual");
  else write_screen(-1, -1, "Automatic");
  write_screen(0, 3, "Default: ");
  if (mode_sel == 0) 
  {
    write_screen(-1, -1, "N/A");
  }
  else
  {
    if (def_sel == 0) write_screen(-1, -1, "Low");
    else if (def_sel == 1) write_screen(-1, -1, "Medium");
    else write_screen(-1, -1, "High"); 
  }
}
