/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 3 - Motors>
*
* File: <assignment3.c>
*
* Description: This file contains the main function used to make the program run.
**************************************************************/
#include "motorsController.h"

int main(void) {
    signal(SIGINT, cleanUp);

    printf("pin set\n");
    pinSet();
    printf("motor set\n");
    motorsSet();

    printf("motor run\n");
    runMotors();

    return 0;
}
