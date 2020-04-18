#ifndef ENCODERCONTROLLER_H_   
#define ENCODERCONTROLLER_H_
#include "motorsController.h"

#define NUMBER_OF_MOTORS    2 //This defines the number of motors being used.

void ecoderSet(void);

float calculateSpeed(int num);

void writeSpeed(int motor, float speed);

float readSpeed(int motor);

void *useEncoder(void *ptr);

#endif
