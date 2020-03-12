/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 2 - >
*
* File: <echoSensor.c>
*
* Description: 
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "echoSensor.h"

#define ECHO        22 //GPIO 6
#define TRIGGER     21 //GPIO 5
#define SPEED_SOUND 34300.0f //in centimeters per second
#define TWO         2.0f

//this calculates the distance based on the time the echo took
//to return to the sensor. distance = (time * speed of sound) / 2
float calculateDistance(float time) {
    printf("getting distance with time: %f\n", time);
    return (time * SPEED_SOUND) / TWO;
}

void pinSet(void) {
    wiringPiSetup();

    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
}

void prepareTrigger(void) {
    printf("Preparing trigger.\n");
    digitalWrite(TRIGGER, LOW);
    sleep(1);

    digitalWrite(TRIGGER, HIGH);
    sleep(0.00001);
    digitalWrite(TRIGGER, LOW);
}

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

float getDistance(void) {
    prepareTrigger();
    return calculateDistance(getTime());
}

void displayDistance(void) {
    printf("The distance is: %.2f cm\n", getDistance());
}
