/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name:
* Student ID:
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1b.c>
*
* Description:
*
**************************************************************/
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include "assigment1b.h"

#define OUTPUT  "out"
#define HIGH    "1"
#define LOW     "0"
#define RED     "17"
#define YELLOW  "27"
#define GREEN   "22"

void pinMode(char *pin, char *mode) {
    FILE *export;
    export = fopen("/sys/class/gpio/export", "w");
    fwrite(pin, 1, sizeof(pin), export);
    fclose(export);

    char path[] = "/sys/class/gpio/gpio";
    strcat(path,pin);
    strcat(path,"/direction");

    FILE *direction;
    direction = fopen(path, "w");
    fwrite(mode, 1, sizeof(mode), direction);
    fclose(direction);
}

void digitalWrite(char *pin, char *state) {
    char path[] = "/sys/class/gpio/gpio"
    strcat(path, pin);
    strcat(path, "/value");

    FILE *value;
    value = fopen(path, "w");
    fwrite(state, 1, sizeof(state), value);
    fclose(value);
}

void cleanUp(char *pin) {
    FILE *unexport;
    unexport = fopen("/sys/class/gpio/unexport","w");
    fwrite(pin, 1, sizeof(pin), unexport);
    fclose(unexport);
}

int main(void) {
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);

    int cycle = 3;
    for (int i = 0; i < 3; ++i) {
        digitalWrite(GREEN, HIGH);
        //sleep(6);
        digitalWrite(GREEN, LOW);

        digitalWrite(YELLOW, HIGH);
        //sleep(1.5);
        digitalWrite(YELLOW, LOW);

        digitalWrite(RED, HIGH);
        //sleep(5);
        digitalWrite(RED, LOW);
    }

    cleanUp(GREEN);
    cleanUp(YELLOW);
    cleanUp(RED);
}