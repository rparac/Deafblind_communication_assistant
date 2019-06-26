#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "structs.h"

#define N_OF_MOTORS 6

extern brailleEncoding table[37];

void init_motors();

void stop_all();

void execute_instruction(brailleEncoding instruction);

#endif
