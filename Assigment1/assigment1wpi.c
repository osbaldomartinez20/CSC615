#include <stdio.h>
#include <wiringPi.h>
#include "assigment1wpi.h"

#define RED    0
#define YELLOW 2
#define GREEN  3
#define CYCLES 3

void pinSet() {
    wiringPiSetup();

    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
}

void pinWrite() {
    digitalWrite(GREEN, HIGH);
    delay(6000);
    digitalWrite(GREEN, LOW);

    digitalWrite(YELLOW, HIGH);
    delay(1500);
    digitalWrite(YELLOW, LOW);

    digitalWrite(RED, HIGH); //On
    delay(5000);           //in ms
    digitalWrite(RED, LOW); //Off
}

int main(void) {
    printf("Starting the cycles ...\n");

    pinSet();

    for(int i = 0; i < CYCLES; ++i) {
        pinWrite();
    }

    return 0;
}
