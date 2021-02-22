/* 
 * Filename: PressureSensors.h
 * Author: Kyle Bannerman
 * Date Created: 02/22/2021
 * Date of Last Edit: 02/22/2021
 * File Purpose: interfacing with pressure sensors
 */


// retrieve voltage values of sensor, converting to pressure
float read_pressure(int pin);


 // convert voltage to pressure value
float convert_pressure(int v);



