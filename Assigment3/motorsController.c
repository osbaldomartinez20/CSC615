#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTOR_ONE_ENABLER       0  //pin 11(GPIO 17)
#define MOTOR_ONE_CONTROL       2  //pin 13(GPIO 27)
#define MOTOR_ONE_OTHER_CONTROL 3  //pin 15(GPIO 22)

#define MOTOR_TWO_ENABLER       6  //pin 22(GPIO 25)
#define MOTOR_TWO_CONTROL       4  //pin 16(GPIO 23)
#define MOTOR_TWO_OTHER_CONTROL 5  //pin 18(GPIO 24)

void pinSet() {
    wiringPiSetUp();

    pinMode(MOTOR_ONE_ENABLER, OUTPUT);
    pinMode(MOTOR_ONE_CONTROL, OUTPUT);
    pinMode(MOTOR_ONE_OTHER_CONTROL, OUTPUT);

    pinMode(MOTOR_TWO_ENABLER, OUTPUT);
    pinMode(MOTOR_TWO_CONTROL, OUTPUT);
    pinMode(MOTOR_TWO_OTHER_CONTROL, OUTPUT);
}

