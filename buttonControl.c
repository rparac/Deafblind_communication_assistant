#include <stdio.h>
#include <wiringPi.h>
#include "buttonControl.h"

const int buttonPins[N_OF_BUTTON] = {29, 27, 28, 24, 25, 23, 26};

void init_buttons() {
    for (int i = 0; i < N_OF_BUTTON; i++) {
        pinMode(buttonPins[i], INPUT);
    }
}

brailleEncoding readChar() {
    brailleEncoding encoding = {'?', {0, 0, 0, 0, 0, 0}};

    //while enter is not pressed read the encoding
    while (!digitalRead(buttonPins[CONTROL])) {
        for (int i = 0; i < N_OF_BUTTON - 1; i++) {
            //read the pins
            if (digitalRead(buttonPins[i])) {
                //	printf("%d",i);
                encoding.pins[i] = 1;
            }
        }
    }

    // wait until pin is released

    while (digitalRead(buttonPins[CONTROL]));
    delay(100);

    return encoding;
}
