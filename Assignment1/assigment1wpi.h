/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1wpi.h>
*
* Description: This is the header file used by assigment1wpi.c, which uses
*              the wiringPI libary to use GPIO pins to turn
*              on and off LED lights to make a trafic light demo.
**************************************************************/
#ifndef ASSIGMENT1WPI_H_   
#define ASSIGMENT1WPI_H_

//Sets up the three pins in order to be able to turn off or on the LEDs.
void pinSet();

//Makes the trafic light demo happen by writing to pins.
void pinWrite();
#endif