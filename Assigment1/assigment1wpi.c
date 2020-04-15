/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1wpi.c>
*
* Description: This file contains the code necesary to run the trafic light
*              demo using the wiringPi library.
**************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "assigment1wpi.h"

#define RED    0
#define YELLOW 2
#define GREEN  3
#define CYCLES 3


//This function sets the pins to OUTPUT in order to be able to
//turn on and off the LED lights connected to the pins defined by their color name variables.
void pinSet() {
    wiringPiSetup();
    
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

//This function is the driving force of the trafic light demo
//It turns on the LED on(HIGH) for a set time in milisec, then it turns it off(LOW) and does the same thing for the next light.
//It goes through the cycle of GREEN light -> YELLLOW light -> RED light
void pinWrite() {
    digitalWrite(GREEN, HIGH);
    delay(6000);
    digitalWrite(GREEN, LOW);

    digitalWrite(YELLOW, HIGH);
    delay(1500);
    digitalWrite(YELLOW, LOW);

    digitalWrite(RED, HIGH); //On
    delay(5000);           //in ms
    digitalWrite(RED, LOW); //Off
}

int main(void) {
    printf("Starting the cycles ...\n");

    pinSet();

    //This repeats the trafic light demo a CYCLES number of times.
    for(int i = 0; i < CYCLES; ++i) {
        pinWrite();
    }

    return 0;
}
