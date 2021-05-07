/* 
 * Filename: LCDScreen.h
 * Author: Kyle Bannerman
 * Date Created: 02/23/2021
 * Date of Last Edit: 05/07/2021
 * File Purpose: interfacing with LCD screen using I2C
 */


// init screen
void init_screen();

// write to screen through serial
void write_screen(int col, int row, char *msg);


// clear the screen
void clear_screen();


// write the pressure values to the LCD screen
void write_pressure_vals(float input_pressure, int mode_sel, int def_sel);
