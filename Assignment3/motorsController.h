/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 3 - Motors>
*
* File: <motorsController.h>
*
* Description: This header files defines the functions to be
*              be implemented in motorsController.c
**************************************************************/
#ifndef MOTORSCONTROLLER_H_   
#define MOTORSCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MAX_INTENCITY           100 //the max range the motor can reach in power.
#define MIN_INTENCITY            0  //the min range the motor can reach in power.

#define MOTOR_ONE_ENABLER        0  //pin 11(GPIO 17)
#define MOTOR_ONE_CONTROL        2  //pin 13(GPIO 27)
#define MOTOR_ONE_CONTROL_TWO    3  //pin 15(GPIO 22)

#define MOTOR_TWO_ENABLER        6  //pin 22(GPIO 25)
#define MOTOR_TWO_CONTROL        4  //pin 16(GPIO 23)
#define MOTOR_TWO_CONTROL_TWO    5  //pin 18(GPIO 24)

#define FORWARD                  0  
#define BACKWARD                 1

#define MOTOR_ONE_F              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FORWARD) //makes motor one go forward.
#define MOTOR_TWO_F              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FORWARD) //makes motor two go forward.

#define MOTOR_ONE_B              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, BACKWARD) //makes motor one go backward.
#define MOTOR_TWO_B              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, BACKWARD) //makes motor two go backward.

#define MOTOR_ONE_F_D            motorMoveWithDecreasingPow(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FORWARD) //makes motor one go forward and decreases power.
#define MOTOR_TWO_F_D            motorMoveWithDecreasingPow(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FORWARD) //makes motor two go forward and decreases power.

#define MOTOR_ONE_B_D            motorMoveWithDecreasingPow(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, BACKWARD) //makes motor one go backward and decreases power.
#define MOTOR_TWO_B_D            motorMoveWithDecreasingPow(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, BACKWARD) //makes motor two go backward and decreases power.

#define MOTOR_ONE_S              motorStop(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO) //makes motor one stop.
#define MOTOR_TWO_S              motorStop(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO) //makes motor two stop.

//It sets up the pins so that they can be used by the program.
void pinSet(void);

//It sets up the motors so that they can be used by the program.
void motorsSet(void);

//tells the motor enabler pin #, the pin #'s of the controllers, and the direction(BACKWARD or FORWARD)
//and makes the motor move to that direction.
void motorMove(int enabler, int control, int control2, int direction);

//tells the motor enabler pin #, the pin #'s of the controllers, and the direction(BACKWARD or FORWARD)
//and makes the motor move to that direction also decraeses power.
void motorMoveWithDecreasingPow(int enabler, int control, int control2, int direction);

//tales the motor enabler pin # and the pin #'s of the controllers
//and makes the motor stop.
void motorStop(int enabler, int control, int control2);

//Thread function that makes the motor go forward.
//the void pointer must point to either 1 or 2 to indicate the motor to control.
//returns NULL.
void *motorToControlForward(void *ptr);

//Thread function that makes the motor go forward with decreasing power.
//the void pointer must point to either 1 or 2 to indicate the motor to control.
//returns NULL.
void *motorToControlForward2(void *ptr);

//Thread function that makes the motor go backward.
//the void pointer must point to either 1 or 2 to indicate the motor to control. 
//returns NULL.
void *motorToControlBackward(void *ptr);

//Thread function that makes the motor go backward with decreasing power.
//the void pointer must point to either 1 or 2 to indicate the motor to control.
//returns NULL.
void *motorToControlBackward2(void *ptr);

//Runs the motors forwards and then backwards by making use of threads.
void runMotors(void);

//Runs the motors forwards and then backwards with no threads. 
void runMotors2(void);

//Runs the motors forwards with decreasing power by making use of threads.
void runMotorsWithDiffPower(void)

//Runs the motors backwards with decreasing power with no threads.
void runMotorsWithDiffPower2(void)

//This function stops the motors for a clean exit from program.
//Use it when detecting a ctr+c just in case motors are running at that time.
void cleanUp();

#endif