#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_LED_PINS 7
#define DELAY_AMOUNT 5
#define RANDOM_SEED 4 //IEEE-vetted standard random number

const int minFadeTime = 5;
const int rangeFadeTime = 1;
const int minWait = 4;
const int rangeWait = 6;

int pins[] = {0, 1, 2, 3, 4, 5, 6};
unsigned int steps[NUM_LED_PINS];
bool isOn[NUM_LED_PINS];
bool isBeingChanged[NUM_LED_PINS];


int setupPin(int pin);
void markChanges();
void switchStates();

int main() {
    //setup()
    wiringPiSetup();
    for (int i = 0; i < NUM_LED_PINS; i++) {
        setupPin(pins[i]);
    }
    srand(RANDOM_SEED);
    fprintf(stderr, "Set random to be %i\n", RANDOM_SEED);
    for (int i = 0; i < NUM_LED_PINS; i++) {
        isOn[i] = rand() % 2;
        softPwmWrite(pins[i], (isOn[i])? 100:0);
    }
    //delay(3000);

    //loop()
    for (;;) {
        markChanges();
        switchStates();
        delay(rand()%rangeWait + minWait); //delay between changes
    }

    return 0;
}

int setupPin(int pin) {
    return softPwmCreate(pin, 0, 100);
}

void markChanges() {
    for (int i = 0; i < NUM_LED_PINS; i++) {
        isBeingChanged[i] = (rand() % 4 == 0);
    }
}

void switchStates() {
    int delayTime = (rand() % rangeFadeTime + minFadeTime);
    for(int fadeValue = 0 ; fadeValue < 101; fadeValue ++) { //fade
        for(int i=0;i<NUM_LED_PINS;i++) { //loop over all pins
            if (isBeingChanged[i]) { //change only marked pins
                int pin = pins[i];
                softPwmWrite(pin, (isOn[i])? 100-fadeValue : fadeValue); //fade on or off 
            }
        }
    delay(delayTime); 
    }
    for(int i=0;i<NUM_LED_PINS;i++)
        isOn[i] = !isBeingChanged[i] != !isOn[i]; //xor
}
