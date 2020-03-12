/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2 - Tapeless Ruler>
*
* File: <assigment2.c>
*
* Description: The main function helps in making an infinite loop
*              to have the sensor constantly measure a distance.
**************************************************************/
#include <stdio.h>
#include "echoSensor.h"


//The main function is used to make an infinite loop that constantly measures the distance 
//that the echo traveled.
int main(void) {
    pinSet();
    for (; ;) {
        displayDistance();
    }
    return 0;
}
