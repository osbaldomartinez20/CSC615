/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2 - >
*
* File: <assigment2.c>
*
* Description: 
**************************************************************/
#include <stdio.h>
#include "echoSensor.h"

int main(void) {
    pinSet();
    for (; ; ) {
        displayDistance();
    }
    return 0;
}
