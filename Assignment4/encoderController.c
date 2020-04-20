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
    if (wiringPiSPISetup (CHIP_CHANNEL, CLOCK_SPEED) < 0) {
        printf ("Unable to open SPI device 0:\n") ;
        exit (1) ;
   }
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

int readPulses(double time) {
    struct timespec start;
    int count = 0;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double end = start.tv_sec + start.tv_nsec + time;

    while (end > (start.tv_nsec + start.tv_sec)) {
        if(digitalRead(SPEED_SENSOR_PIN)) {
            count++;
            while(digitalRead(SPEED_SENSOR_PIN)){}
        }
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

    return count;
}

void getDataFromChip(void) {
    chipSet();
    u_int8_t command[COMMAND_LENGTH] = {ARRAY_INIT_VAL};
    
    //enables writing to chip.
    command[0] = 1; //B7
    command[1] = 0; //B6
    command[2] = 0; //B5
    command[3] = 0; //B4
    command[4] = 1; //B3
    command[5] = 0; //B2
    command[6] = 0; //B1
    command[7] = 0; //B0
    wiringPiSPIDataRW (CHIP_CHANNEL, command, COMMAND_LENGTH);

    //write data to chip
    command[0] = 1; //B7
    command[1] = 0; //B6
    command[2] = 1; //B5
    command[3] = 0; //B4
    command[4] = 0; //B3
    command[5] = 0; //B2
    command[6] = 1; //B1
    command[7] = 1; //B0
    wiringPiSPIDataRW (CHIP_CHANNEL, command, COMMAND_LENGTH);

    delay(1000 * TIME_TO_MEASURE);

    //reads the data
    command[0] = 0; //B7
    command[1] = 1; //B6
    command[2] = 0; //B5
    command[3] = 0; //B4
    command[4] = 1; //B3
    command[5] = 0; //B2
    command[6] = 0; //B1
    command[7] = 0; //B0
    wiringPiSPIDataRW(CHIP_CHANNEL, command, COMMAND_LENGTH);

    for(int i = 0; i < COMMAND_LENGTH; i++) {
        printf("Data at %d: %02X\n", i, command[i]);
    }

}

void *useChip(void *ptr) {
    getDataFromChip();
    return NULL;
}

void *useSpeedSensor(void *ptr) {
    double speed = calculateAngularSpeed(readPulses(TIME_TO_MEASURE), TIME_TO_MEASURE);
    printf("The speed is: %f rad/s\n", speed);
    return NULL;
}