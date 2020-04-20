#ifndef ENCODERCONTROLLER_H_   
#define ENCODERCONTROLLER_H_

#include <time.h>
#include <wiringPiSPI.h>
#include "motorsController.h"

#define PI                    3.14159265358979323846  //the value of pi
#define NUMBER_OF_MOTORS      2           //This defines the number of motors being used.
#define PULSES_PER_ROTATION   20          //The number of holes in the wheel encoder. The speed sensor reads each hole as a pulse.
#define SPEED_SENSOR_PIN      27          //pin 36(GPIO 16)
#define TIME_TO_MEASURE       1.0         //Time frame used to measure pulses.
#define CLOCK_SPEED           20000000    //The ls7366r clock speed at 3v3 in HZ.
#define CHIP_CHANNEL          0           //Channel being used by chip.
#define COMMAND_LENGTH        8           //The length of commands for the chip.
#define ARRAY_INIT_VAL        0           //Initial value for array elements.

//It sets up the pins needed for the speed sensor. 
void speedSensorSet(void);

//reads the pulses that the speed sensor sees. It returns the pulses that were counted.
int readPulses(double time);

//calculates and returns angular speed using formula omega = (2*PI*NumberOfPulses) / (Time * PulsesPerRotation)
double calculateAngularSpeed(int totalPulses, double time);

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
