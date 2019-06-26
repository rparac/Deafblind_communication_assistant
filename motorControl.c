#include <stdio.h>
#include <wiringPi.h>
#include "motorControl.h"

const int motorPins[N_OF_MOTORS] = {5, 6, 7, 8, 9, 10};

void init_motors() {
    for (int i = 0; i < N_OF_MOTORS; i++) {
        pinMode(motorPins[i], OUTPUT);
    }
}

void stop_all() {

    execute_instruction(table[0]);
}

void execute_instruction(brailleEncoding instruction) {
    for (int i = 0; i < N_OF_MOTORS; i++) {
        digitalWrite(motorPins[i], instruction.pins[i] ? HIGH : LOW);
    }
}

