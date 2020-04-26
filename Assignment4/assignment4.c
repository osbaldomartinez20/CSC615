/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 4 - Motors and Speed Encoder>
*
* File: <assignment.c>
*
* Description: This file contains the code to make threads that
*              run the motors and make use of speed encoder.
**************************************************************/
#include <signal.h>
#include "encoderController.h"
#include "motorsController.h"

void runMotorSpeedSensor(void) {
    pthread_t thread1, thread2, thread3, thread4;
    int s1, s2, s3, s4, motor1 = 1, motor2 = 2;
    void *m1 = &motor1;
    void *m2 = &motor2;

    printf("initialize threads\n");
    if ((s1 = pthread_create(&thread1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, useSpeedSensor,NULL))) {
        printf("thread creation failed: %i\n", s2);
    }
    if ((s3 = pthread_create(&thread3, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %i\n", s3);
    }
    if ((s4 = pthread_create(&thread4, NULL, useChip,NULL))) {
        printf("thread creation failed: %i\n", s4);
    }

    printf("join threads.\n");
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    pthread_join( thread3, NULL);
    pthread_join( thread4, NULL);
}

int main() {
    signal(SIGINT, cleanUp);

    pinSet();
    motorsSet();
    speedSensorSet();

    runMotorSpeedSensor();
}
