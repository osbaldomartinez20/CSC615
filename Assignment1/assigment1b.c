/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1b.c>
*
* Description: This file contains the code necesary to run the trafic light
*              demo using file I/O (sysfs) operations.
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "assigment1b.h"

#define OUTPUT  "out"
#define HIGH    "1"
#define LOW     "0"
#define RED     "17"
#define YELLOW  "27"
#define GREEN   "22"
#define CYCLES   3

//This function helps in setting the pin up (in this demo only output mode) in /sys/class/gpio/
//by using file I/O (sysfs)
void pinMode(char *pin, char *mode) {
    FILE *export;
    export = fopen("/sys/class/gpio/export", "w");
    if (export == NULL) {
        printf("Error! Could not open /sys/class/gpio/export\n"); 
        printf("Please run executable using sudo.")
        exit(-1);
    }
    fwrite(pin, 1, sizeof(pin), export);
    fclose(export);

    char path[] = "/sys/class/gpio/gpio";
    strcat(path,pin);
    strcat(path,"/direction");

    FILE *direction;
    direction = fopen(path, "w");
    if (direction == NULL) {
        printf("Error! Could not open /sys/class/gpio/gpio%s/direction\n", pin); 
        printf("Please run executable using sudo.")
        exit(-1);
    }
    fwrite(mode, 1, sizeof(mode), direction);
    fclose(direction);
}

//This function allows to either tell the pin to be
//on ("1") or off ("0") through file I/O
void digitalWrite(char *pin, char *state) {
    char path[] = "/sys/class/gpio/gpio";
    strcat(path, pin);
    strcat(path, "/value");

    FILE *value;
    value = fopen(path, "w");
    if (value == NULL) {
        printf("Error! Could not open /sys/class/gpio/gpio%s/value\n", pin); 
        printf("Please run executable using sudo.")
        exit(-1);
    }
    fwrite(state, 1, sizeof(state), value);
    fclose(value);
}

//This function makes the pin to be removed
//from /sys/class/gpio/ by using file I/O
void pinCleanUp(char *pin) {
    FILE *unexport;
    unexport = fopen("/sys/class/gpio/unexport","w");
    if (unexport == NULL) {
        printf("Error! Could not open /sys/class/gpio/unexport\n"); 
        printf("Please run executable using sudo.")
        exit(-1);
    }
    fwrite(pin, 1, sizeof(pin), unexport);
    fclose(unexport);
}

//This function sets up the three pins to be able to turn on LED lights
void pinSet() {
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

//This function is the driving force of the trafic light demo
//It turns on the LED on for a set time in sec, then it turns it off and does the same thing for the next light.
//It goes through the cycle of GREEN light -> YELLLOW light -> RED light.
void pinWrite() {
    digitalWrite(GREEN, HIGH);
    sleep(6);
    digitalWrite(GREEN, LOW);

    digitalWrite(YELLOW, HIGH);
    sleep(1.5);
    digitalWrite(YELLOW, LOW);

    digitalWrite(RED, HIGH);
    sleep(5);
    digitalWrite(RED, LOW);
}

//This function removes all the pins used for the LED lights from /sys/class/gpio/
void pinFlush() {
    pinCleanUp(GREEN);
    pinCleanUp(YELLOW);
    pinCleanUp(RED);
}

int main(void) {
    printf("Starting the cycles ...\n");

    pinSet();
    
    //This repeats the trafic light demo a CYCLES number of times.
    for (int i = 0; i < CYCLES; ++i) {
        pinWrite();
    }

    pinFlush();

    return 0;
}
