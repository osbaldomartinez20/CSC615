/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2>
*
* File: <echosensor.h>
*
* Description: 
**************************************************************/
#ifndef ECHOSENSOR_H_   
#define ECHOSENSOR_H_

float calculateDistance(float time);
void  pinSet(void);
void  prepareTrigger(void);
float getTime(void);
float getDistance(void);
void  displayDistance(void);

#endif