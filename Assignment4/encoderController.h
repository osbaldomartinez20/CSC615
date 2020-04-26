/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Osbaldo Martinez
* Student ID: 916754207
* Project: <Assignment 4 - Motors and Speed Encoder>
*
* File: <motorsController.h>
*
* Description: This header files defines the functions to be
*              be implemented in encoderController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef ENCODERCONTROLLER_H_   
#define ENCODERCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define PI                    3.14159265358979323846  //the value of pi
#define NUMBER_OF_MOTORS      2                       //This defines the number of motors being used.
#define PULSES_PER_ROTATION   20                      //The number of holes in the wheel encoder. The speed sensor reads each hole as a pulse.
#define SPEED_SENSOR_PIN      27                      //pin 36(GPIO 16)
#define TIME_TO_MEASURE       1.0                     //Time frame used to measure pulses.
#define CLOCK_SPEED           200000000               //The ls7366r clock speed at 3v3 in HZ.
#define CHIP_CHANNEL          1                       //Channel being used by chip.
#define COMMAND_LENGTH        8                       //The length of commands for the chip.
#define ARRAY_INIT_VAL        0                       //Initial value for array elements.
#define ENCODER_DIAMETER      2.5                     //in centimeters.

//It sets up the pins needed for the speed sensor. 
void speedSensorSet(void);

//reads the pulses that the speed sensor sees. It returns the pulses that were counted.
int readPulses(double time);

//calculates and returns angular speed using formula omega = (2*PI*NumberOfPulses) / (Time * PulsesPerRotation). Speed in radians per second.
double calculateAngularSpeed(int totalPulses, double time);

//calculates and returns linear speed using formula v = ωr. Speed in meters per second.
double calculateSpeed(double diameter, double angularSpeed);

//It writes the speed to the array containing the speeds of each motor.
void writeSpeed(int motor, double speed);

//It reads the speed of the array containing the speeds of each motor.
double readSpeed(int motor);

//It sets up the chip in order to be used.
void chipSet(void);

//Function that enables gets the data(pulse count) from the chip.
void getDataFromChip(void);

//Function to be used in threads to display the speed read by the speed sensor.
void *useSpeedSensor(void *ptr);

//Function to be used in threads to get data from the chip.
void *useChip(void *ptr);

#endif
