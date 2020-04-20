#include <signal.h>
#include "encoderController.h"
#include "motorsController.h"

void runMotorSpeedSensor(void) {
    pthread_t thread1, thread2;
    int s1, s2, motor1 = 1;
    void *m1 = &motor1;

    printf("initialize threads\n");
    if ((s1 = pthread_create(&thread1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&thread2, NULL, useSpeedSensor, NULL))) {
        printf("thread creation failed: %i\n", s2);
    }

    printf("join threads.\n");
    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
}

int main() {
    signal(SIGINT, cleanUp);

    pinSet();
    motorsSet();
    speedSensorSet();

    runMotorSpeedSensor();
}