#include <stdio.h>
#include <wiringPi.h>
#include "ledMatrix.h"

const int ledPins[N_OF_ROWS + N_OF_COLS] = {1, 2, 3, 0, 4};

const int turnOnTime = 1;

void turn_one_on_off(int row, int column) {
    for (int i = 0; i < N_OF_ROWS; i++) {
        digitalWrite(ledPins[i], i == row ? LOW : HIGH);
    }

    for (int i = 0; i < N_OF_COLS; i++) {
        digitalWrite(ledPins[i + N_OF_ROWS], i == column ? HIGH : LOW);
    }

    delay(turnOnTime);
    digitalWrite(ledPins[row], HIGH);
    digitalWrite(ledPins[column + N_OF_ROWS], LOW);

}


void turn_on(bool matrix[N_OF_ROWS][N_OF_COLS], int time) {
    while (time > 0) {
        int nTurnedOn = 0;
        for (int i = 0; i < N_OF_ROWS; i++) {
            for (int j = 0; j < N_OF_COLS; j++) {
                if (matrix[i][j]) {
                    turn_one_on_off(i, j);
                    nTurnedOn++;
                }
            }
        }
        time -= nTurnedOn * turnOnTime;

        if (nTurnedOn == 0) {
            delay(time);
            time = 0;
        }
    }
}

void init_led() {
    for (int i = 0; i < N_OF_ROWS + N_OF_COLS; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}


void setAll(bool matrix[N_OF_ROWS][N_OF_COLS], bool value) {
    for (int i = 0; i < N_OF_ROWS; i++) {
        for (int j = 0; j < N_OF_COLS; j++) {
            matrix[i][j] = value;
        }
    }

}


/*

int main(void) {
	init();

	bool matrix[N_OF_ROWS][N_OF_COLS];

	setAll(matrix, false);

	for(;;) {
		printf("Turn on\n");

		setAll(matrix, true);
		turn_on(matrix, 1000);
		printf("Turn off\n");
		setAll(matrix, false);
		turn_on(matrix, 1000);
	}
}

*/

