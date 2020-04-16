#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_ONE_ENABLER        0  //pin 11(GPIO 17)
#define MOTOR_ONE_CONTROL        2  //pin 13(GPIO 27)
#define MOTOR_ONE_CONTROL_TWO    3  //pin 15(GPIO 22)

#define MOTOR_TWO_ENABLER        6  //pin 22(GPIO 25)
#define MOTOR_TWO_CONTROL        4  //pin 16(GPIO 23)
#define MOTOR_TWO_CONTROL_TWO    5  //pin 18(GPIO 24)

#define FORWARD                  0
#define BACKWARD                 1

#define MOTOR_ONE_F              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FORWARD)
#define MOTOR_TWO_F              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FORWARD)

#define MOTOR_ONE_B              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, BACKWARD)
#define MOTOR_TWO_B              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, BACKWARD)

#define MOTOR_ONE_S              motorStop(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO)
#define MOTOR_TWO_S              motorStop(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO)

void pinSet(void) {
    wiringPiSetUp();

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
        digitalWrite(control, HIGH)
    }
}

void motorStop(int enabler, int control, int control2) {
    digitalWrite(enabler, LOW);
    digitalWrite(control, LOW);
    digitalWrite(control2,LOW);
}

void *motorToControlForward(void *ptr) {
    int *motor;
    motor = (int *) ptr;
    if (*motor == 1) {
        MOTOR_ONE_F;
    } else {
        MOTOR_TWO_F;
    }

}

void *motorToControlBackward(void *ptr) {
    int *motor;
    motor = (int *) ptr;
    if (*motor == 1) {
        MOTOR_ONE_B;
    } else {
        MOTOR_TWO_B; 
    }
}

void runMotors(void) {
    pthread_t thread1, thread2;
    int i1, i2, s1, s2, motor1 = 1, motor2 = 2;
    int *m1 = &motor1;
    int *m2 = &motor2;

    if ((s1 = pthread_create(&thread1, NULL, motorToControlForward, (void*) motor1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, motorToControlForward, (void*) motor2))) {
        printf("thread creation failed: %i\n", s2);
    }

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    delay(3000);

    MOTOR_ONE_S;
    MOTOR_TWO_S;

    if ((s1 = pthread_create(&thread1, NULL, motorToControlBackward, (void*) motor1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, motorToControlBackward, (void*) motor2))) {
        printf("thread creation failed: %i\n", s2);
    }

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);

    delay(3000);

    MOTOR_ONE_S;
    MOTOR_TWO_S;
}

void cleanUp() {
    MOTOR_ONE_S;
    MOTOR_TWO_S;
    exit(0);
}

int main(void) {

    signal(SIGINT, cleanUp);
    
    while(1) {
    pinSet();
    motorsSet();

    runMotors();

    }
}