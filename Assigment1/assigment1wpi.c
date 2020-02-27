#include <stdio.h>
#include <wiringPi.h>

#define RED 0
#define YELLOW 2
#define GREEN 3

int main(void) {
    printf("Raspberry Pi - Gertboard Blink\n");

    wiringPiSetup();

    pinMode(RED, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);
    
    int cycles = 3;
    for(int i = 0; i < cycles; ++i) {
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

    return 0;
}
