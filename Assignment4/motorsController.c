/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 4 - Motors>
*
* File: <motorsController.c>
*
* Description: This file contains the functions necessary to make the motors move
*              forward and backward plus there is a function to make them stop.
*              There are also functions that cycle through motor movements.
**************************************************************/
//All of the documentation of the functions can be found in motorsController.h
#include "motorsController.h"

//this mutex is to help maintain order when having code in critical sections.
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void pinSet(void) {
    wiringPiSetup();

    pinMode(MOTOR_ONE_ENABLER, OUTPUT);
    pinMode(MOTOR_ONE_CONTROL, OUTPUT);
    pinMode(MOTOR_ONE_CONTROL_TWO, OUTPUT);

    pinMode(MOTOR_TWO_ENABLER, OUTPUT);
    pinMode(MOTOR_TWO_CONTROL, OUTPUT);
    pinMode(MOTOR_TWO_CONTROL_TWO, OUTPUT);
}

void motorsSet(void) {
    int status;

    if((status = softPwmCreate(MOTOR_ONE_ENABLER, 0, 100)) != 0) {
        printf("PWN could not be established.\n");
        exit(status);
    }

    if((status = softPwmCreate(MOTOR_TWO_ENABLER, 0, 100)) != 0) {
        printf("PWN could not be established.\n");
        exit(status);
    }
}

void motorMove(int enabler, int control, int control2, int direction) {
    digitalWrite(enabler, HIGH);
    softPwmWrite(enabler, 75);

    if(direction) {
        digitalWrite(control, LOW);
        digitalWrite(control2, HIGH);
    } else {
        digitalWrite(control2, LOW);
        digitalWrite(control, HIGH);
    }
}

void motorMoveWithDecreasingPow(int enabler, int control, int control2, int direction) {
    digitalWrite(enabler, HIGH);
    softPwmWrite(enabler, 0);

    if (direction) {
        digitalWrite(control, LOW);
        digitalWrite(control2, HIGH);
    } else {
        digitalWrite(control2, LOW);
        digitalWrite(control, HIGH);
    }

    pthread_mutex_lock( &mutex1 );
    printf("motor moving:\n");
    for (int intencity = MAX_INTENCITY; intencity >= MIN_INTENCITY; intencity -= 10) {
        printf("motor power: %i\n", intencity);
        softPwmWrite(enabler, intencity);
        delay(1000);
    }
    printf("stopping motor.\n");
    motorStop(enabler, control, control2);
    pthread_mutex_unlock( &mutex1 );
}

void motorStop(int enabler, int control, int control2) {
    digitalWrite(enabler, LOW);
    digitalWrite(control, LOW);
    digitalWrite(control2,LOW);
}

void *motorToControlForward2(void *ptr) {
    int motor;
    motor = *((int *) ptr);
    if (motor == 1) {
        MOTOR_ONE_F_D;
    } else {
        MOTOR_TWO_F_D;
    }
    return NULL;
}

void *motorToControlForward(void *ptr) {
    int motor;
    motor = *((int *) ptr);
    if (motor == 1) {
        MOTOR_ONE_F;
    } else {
        MOTOR_TWO_F;
    }
    return NULL;
}

void *motorToControlBackward2(void *ptr) {
    int motor;
    motor = *((int *) ptr);
    if (motor == 1) {
        MOTOR_ONE_B_D;
    } else {
        MOTOR_TWO_B_D; 
    }
    return NULL;
}

void *motorToControlBackward(void *ptr) {
    int motor;
    motor = *((int *) ptr);
    if (motor == 1) {
        MOTOR_ONE_B;
    } else {
        MOTOR_TWO_B; 
    }
    return NULL;
}

void runMotors(void) {
    printf("initialize vars\n");
    pthread_t thread1, thread2, t1, t2;
    int s1, s2, motor1 = 1, motor2 = 2;
    void *m1 = &motor1;
    void *m2 = &motor2;

    printf("initialize threads\n");
    if ((s1 = pthread_create(&thread1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %i\n", s2);
    }

    printf("join threads.\n");
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    delay(3000);

    printf("stop motors\n");
    MOTOR_ONE_S;
    MOTOR_TWO_S;	

    printf("initialize other threads.\n");
    if ((s1 = pthread_create(&t1, NULL, motorToControlBackward, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&t2, NULL, motorToControlBackward, m2))) {
        printf("thread creation failed: %i\n", s2);
    }

	printf("join other threads.\n");
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);

    delay(3000);

	printf("stop motors\n");
    MOTOR_ONE_S;
    MOTOR_TWO_S;
}

void runMotors2(void) {
    printf("motors go F\n");
    MOTOR_ONE_F;
    MOTOR_TWO_F;

    delay(3000);

    printf("motors go S\n");
    MOTOR_ONE_S;
    MOTOR_TWO_S;

    delay(100);

    printf("motors go B\n");
    MOTOR_ONE_B;
    MOTOR_TWO_B;

    delay(3000);

    printf("motors go S\n");
    MOTOR_ONE_S;
    MOTOR_TWO_S;
}

void runMotorsWithDiffPower(void) {
    printf("initialize vars\n");
    pthread_t thread1, thread2;
    int s1, s2, motor1 = 1, motor2 = 2;
    void *m1 = &motor1;
    void *m2 = &motor2;

    printf("initialize threads\n");
    if ((s1 = pthread_create(&thread1, NULL, motorToControlForward2, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, motorToControlForward2, m2))) {
        printf("thread creation failed: %i\n", s2);
    }

    printf("join threads.\n");
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
}

void runMotorsWithDiffPower2(void) {
    MOTOR_ONE_B_D;
    MOTOR_TWO_B_D;
}

void cleanUp() {
    MOTOR_ONE_S;
    MOTOR_TWO_S;
    exit(0);
}
