/* 
 * Filename: MotorControl.h
 * Author: Kyle Bannerman
 * Date Created: 05/06/2021
 * Date of Last Edit: 05/06/2021
 * File Purpose: nonblocking control of the motor
 */


// set the max speed for the motor
void set_max();


// run motor in the forwards direction
void run_mot_forward(int mot_speed);


// run the motor in the reverse direction
void run_mot_backward(int mot_speed);
