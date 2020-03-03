/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1b.h>
*
* Description: This is the header file used by assigment1b.c, which uses
*              a file I/O (sysfs) implementation to use GPIO pins to turn
*              on and off LED lights to make a trafic light demo.
**************************************************************/
#ifndef ASSIGMENT1B_H_   
#define ASSIGMENT1B_H_

//It sets the pin up with a mode in order to be able to use pin.
//Expects input:
//pin -> a string with the GPIO number of the pin.
//mode -> a string with either "in" or "out" depending on what you want to do with the pin.
void pinMode(char *pin, char *mode);

//Writes to pin to either be on or off.
//Expects input:
//pin -> a string with the GPIO number of the pin.
//state -> a string with either "1" (on) or "0" (off).
void digitalWrite(char *pin, char *state);

//Makes sure that the pin is closed.
//Expects input:
//pin -> a string with the GPIO number of the pin.
void cleanUp(char *pin);

//Sets up the three pins in order to be able to turn off or on the LEDs.
void pinSet();

//Makes the trafic light demo happen by writing to pins.
void pinWrite();

//Closes the pins used tyo power LEDs.
void pinClean();
#endif