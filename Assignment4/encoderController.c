#include "encoderController.h"

//this mutex is to help maintain order when having code in critical sections.
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

//This array contains the speed of each motor.
//Motor 1 at index 0, Motor 2 at index 1 and so on.
float MOTORS_SPEED[NUMBER_OF_MOTORS]={0};

void writeSpeed(int motor, float speed) {
    pthread_mutex_lock( &mutex1 );
    MOTORS_SPEED[motor] = speed;
    pthread_mutex_unlock( &mutex1 );
}

float readSpeed(int motor) {
    pthread_mutex_lock( &mutex1 );
    return MOTORS_SPEED[motor];
    pthread_mutex_unlock( &mutex1 );
}

void ecoderSet(void) {
    
}