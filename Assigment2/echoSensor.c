/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2 - Tapeless Ruler>
*
* File: <echoSensor.c>
*
* Description: The functions in this file help in calculating
*              the time the echo takes to come back, the distance
*              between the sensor and an object, setting up the 
*              GPIO pins, setting up the echo and the trigger in the sensor,
*              and displaying the data that was calculated.
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "echoSensor.h"

#define ECHO        22 //GPIO 6
#define TRIGGER     21 //GPIO 5
#define SPEED_SOUND 34300.0f //in centimeters per second
#define TWO         2.0f //two as a float

//this calculates the distance based on the time the echo took
//to return to the sensor. distance = (time * speed of sound) / 2
//accepts time as a float and returns the disttance as a float
float calculateDistance(float time) {
    printf("getting distance with time: %f\n", time);
    return (time * SPEED_SOUND) / TWO;
}

//This function sets up the pins to be used by
//the trigger and echop in the sensor.
void pinSet(void) {
    wiringPiSetup();

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}

//This function prepares the trigger to be used
//to send and receive the echo.
void prepareTrigger(void) {
    printf("Preparing trigger.\n");
    digitalWrite(TRIGGER, LOW);
    sleep(1);

    digitalWrite(TRIGGER, HIGH);
    sleep(0.00001);
    digitalWrite(TRIGGER, LOW);
}

//calculates the time that it took for the echo
//to come back to the sensor.
float getTime(void) {
    struct timespec start, end;

    while (!digitalRead(ECHO)) {
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

    while (digitalRead(ECHO)) {
        clock_gettime(CLOCK_MONOTONIC, &end);
    }

    float total_time;
    total_time = (end.tv_sec - start.tv_sec) * 1e9;
    total_time = (total_time + (end.tv_nsec - start.tv_nsec)) * 1e-9;


    return total_time;
}

//Returns the distance as a float. This function first triggers the triggers,
//then calculates time and finally it returns the calculated distance.
float getDistance(void) {
    prepareTrigger();
    return calculateDistance(getTime());
}

//This function displays the distance calculated by how long the
//echo took to come back.
void displayDistance(void) {
    printf("The distance is: %.2f cm\n", getDistance());
}
