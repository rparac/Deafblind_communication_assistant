
#ifndef STRUCTS_H
#define STRUCTS_H

#define N_OF_PINS 6


typedef struct brailleEncoding {
    char symbol;
    int pins[N_OF_PINS];
} brailleEncoding;

#endif
