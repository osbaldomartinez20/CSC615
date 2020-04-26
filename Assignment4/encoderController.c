/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 4 - Motors and Speed Encoder>
*
* File: <encoderController.c>
*
* Description: This file contains the functions necessary to make the speed
*              encoder count and to display the speed given the encoder's info and
*              the sensor's count.
**************************************************************/
//All of the documentation of the functions can be found in encoderController.h
#include "encoderController.h"

//this mutex is to help maintain order when having code in critical sections.
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

//This array contains the speed of each motor.
//Motor 1 at index 0, Motor 2 at index 1 and so on.
//Speed is in rad/s.
double MOTORS_SPEED[NUMBER_OF_MOTORS]={ARRAY_INIT_VAL};

void speedSensorSet(void) {
    wiringPiSetup();

    pinMode(SPEED_SENSOR_PIN, INPUT);
}

void chipSet(void) {
	wiringPiSetup();
    if (wiringPiSPISetup (CHIP_CHANNEL, CLOCK_SPEED) < 0) {
        printf ("Unable to open SPI device 0:\n") ;
        exit (1) ;
   }

    pinMode(10,OUTPUT);
}

void writeSpeed(int motor, double speed) {
    pthread_mutex_lock( &m );
    MOTORS_SPEED[motor] = speed;
    pthread_mutex_unlock( &m );
}

double readSpeed(int motor) {
    pthread_mutex_lock( &m );
    return MOTORS_SPEED[motor];
    pthread_mutex_unlock( &m );
}

double calculateAngularSpeed(int totalPulses, double time) {
    return (2.0 * PI * totalPulses) / (time * PULSES_PER_ROTATION);
}

double calculateSpeed(double diameter, double angularSpeed) {
    return ((diameter / 2) / 100) * angularSpeed;
}

int readPulses(double time) {
    int count = 0;
    double start = millis();
    double end = start + (1000 * time);
    printf("start: %f, end: %f\n", start, end);

    while (end > millis()) {
        if(digitalRead(SPEED_SENSOR_PIN)) {
            count++;
            while(digitalRead(SPEED_SENSOR_PIN)){}
        }
    }
    printf("Total count: %d\n", count);

    return count;
}

void getDataFromChip(void) {
    chipSet();
    u_int8_t command[COMMAND_LENGTH] = {ARRAY_INIT_VAL};
    
    //enables writing to chip.
   // digitalWrite(10,LOW);
    command[0] = 0x88; 
    wiringPiSPIDataRW (CHIP_CHANNEL, command, 8);

    //write data to chip
    command[0] = 0x00; 
    wiringPiSPIDataRW (CHIP_CHANNEL, command, 8);
   // digitalWrite(10,HIGH);

    delay(10);

   // digitalWrite(10,LOW);
    command[0] = 0x98;
    wiringPiSPIDataRW(0, command, 8);
    for (int i = 0; i < 4; i++) {
	   command[0] = 0x00;
	  wiringPiSPIDataRW(0, command, 1);
    }
   // digitalWrite(10, HIGH);

    delay(10);

   // digitalWrite(10,LOW);
    command[0] = 0xE0;
    wiringPiSPIDataRW(0, command,1);
   // digitalWrite(10, HIGH);

    delay(1000);  

    //reads the data
   // digitalWrite(10,LOW);
    command[0] = 0x70;
    wiringPiSPIDataRW(CHIP_CHANNEL, command, 8);

   // digitalWrite(10,HIGH);
    

    for(int i = 0; i < COMMAND_LENGTH; i++) {
        printf("Data at %d: %02X\n", i, command[i]);
    }


}

void *useChip(void *ptr) {
    getDataFromChip();
    return NULL;
}

void *useSpeedSensor(void *ptr) {
    double aSpeed = calculateAngularSpeed(readPulses(TIME_TO_MEASURE), TIME_TO_MEASURE);
    double speed = calculateSpeed(ENCODER_DIAMETER, aSpeed);
    printf("The angular speed is: %f rad/s\n", aSpeed);
    printf("The linear speed is: %f m/s\n", speed);
    return NULL;
}
