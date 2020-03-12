/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2 - Tapeless Ruler>
*
* File: <echosensor.h>
*
* Description: This header files defines the functions to be
*              be implemented in echoSensor.c
**************************************************************/
#ifndef ECHOSENSOR_H_   
#define ECHOSENSOR_H_

//Takes a float variable that indicates the time it
//took the echo to come back.
//It returns a float with distance measured by the the echo.
float calculateDistance(float time);

//This function sets the pins being used by the echo sensor.
void  pinSet(void);

//This function prepares the trigger to send out the echo.
void  prepareTrigger(void);

//This function returns the time as a float it took for the echo to
//come back.
float getTime(void);

//This function returns a float with the distance. This function also triggers the Trigger
//in the sensor.
float getDistance(void);

//This function displays the distance that was calculated by using the echo.
void  displayDistance(void);

#endif