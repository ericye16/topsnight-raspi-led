#include <wiringPi.h>
//#include <softPwm.h>
#define NUM_PINS 7

int pins[] = {0, 1, 2, 3, 4, 5, 6};

main() {
    //setup()
    wiringPiSetup();
    for (int i = 0; i < NUM_PINS; i++) {
        pinMode(pins[i], OUTPUT);
    }

    //loop()
    for (;;) {
        for (int i = 0; i< NUM_PINS; i++) {
            digitalWrite(pins[i], HIGH);
        }
        delay(500);
        for (int i = 0; i < NUM_PINS; i++) {
            digitalWrite(pins[i], LOW);
        }
        delay(500);
    }
}
