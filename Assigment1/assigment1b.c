/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 1 - Traffic Light>
*
* File: <assigment1b.c>
*
* Description:
*
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OUTPUT  "out"
#define HIGH    "1"
#define LOW     "0"
#define RED     "17"
#define YELLOW  "27"
#define GREEN   "22"
#define CYCLES   3

void pinMode(char *pin, char *mode) {
    FILE *export;
    export = fopen("/sys/class/gpio/export", "w");
    if(export == NULL) {
        printf("Error! Could not open /sys/class/gpio/export\n"); 
        exit(-1);
    }
    fwrite(pin, 1, sizeof(pin), export);
    fclose(export);

    char path[] = "/sys/class/gpio/gpio";
    strcat(path,pin);
    strcat(path,"/direction");

    FILE *direction;
    direction = fopen(path, "w");
    if(direction == NULL) {
        printf("Error! Could not open /sys/class/gpio/gpio%s/direction\n", pin); 
        exit(-1);
    }
    fwrite(mode, 1, sizeof(mode), direction);
    fclose(direction);
}

void digitalWrite(char *pin, char *state) {
    char path[] = "/sys/class/gpio/gpio";
    strcat(path, pin);
    strcat(path, "/value");

    FILE *value;
    value = fopen(path, "w");
    if(direction == NULL) {
        printf("Error! Could not open /sys/class/gpio/gpio%s/value\n", pin); 
        exit(-1);
    }
    fwrite(state, 1, sizeof(state), value);
    fclose(value);
}

void cleanUp(char *pin) {
    FILE *unexport;
    unexport = fopen("/sys/class/gpio/unexport","w");
    if(direction == NULL) {
        printf("Error! Could not open /sys/class/gpio/unexport\n"); 
        exit(-1);
    }
    fwrite(pin, 1, sizeof(pin), unexport);
    fclose(unexport);
}

void pinSet() {
    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

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

void pinClean() {
    cleanUp(GREEN);
    cleanUp(YELLOW);
    cleanUp(RED);
}

int main(void) {
    printf("Starting the cycles ...\n");

    pinSet();
    

    for (int i = 0; i < CYCLES; ++i) {
        pinWrite();
    }
    
    pinClean();

    return 0;
}
