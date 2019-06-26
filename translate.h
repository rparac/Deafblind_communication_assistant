#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdbool.h>
#include "structs.h"

#define EMPTY 0
#define DIGIT 35
#define N_OF_ROWS 3
#define N_OF_COLS 2

brailleEncoding get_special(char c);

void print(struct brailleEncoding braille, const int time);

void setMatrix(bool matrix[3][2], brailleEncoding braille);

int braille_to_output(brailleEncoding encoding, bool isDigit);

void init();

void process_character(char c, const int time);

int main(int argc, char **argv);

struct brailleEncoding table[37] = {
        {' ',  {0, 0, 0, 0, 0, 0}},   //  0 -> space
        {'a',  {1, 0, 0, 0, 0, 0}},   //  1 -> a
        {'b',  {1, 0, 1, 0, 0, 0}},   //  2 -> b
        {'c',  {1, 1, 0, 0, 0, 0}},   //  3 -> c
        {'d',  {1, 1, 0, 1, 0, 0}},   //  4 -> d
        {'e',  {1, 0, 0, 1, 0, 0}},   //  5 -> e
        {'f',  {1, 1, 1, 0, 0, 0}},   //  6 -> f
        {'g',  {1, 1, 1, 1, 0, 0}},   //  7 -> g
        {'h',  {1, 0, 1, 1, 0, 0}},   //  8 -> h
        {'i',  {0, 1, 1, 0, 0, 0}},   //  9 -> i
        {'j',  {0, 1, 1, 1, 0, 0}},   // 10 -> j
        {'k',  {1, 0, 0, 0, 1, 0}},   // 11 -> k
        {'l',  {1, 0, 1, 0, 1, 0}},   // 12 -> l
        {'m',  {1, 1, 0, 0, 1, 0}},   // 13 -> m
        {'n',  {1, 1, 0, 1, 1, 0}},   // 14 -> n
        {'o',  {1, 0, 0, 1, 1, 0}},   // 15 -> o
        {'p',  {1, 1, 1, 0, 1, 0}},   // 16 -> p
        {'q',  {1, 1, 1, 1, 1, 0}},   // 17 -> q
        {'r',  {1, 0, 1, 1, 1, 0}},   // 18 -> r
        {'s',  {0, 1, 1, 0, 1, 0}},   // 19 -> s
        {'t',  {0, 1, 1, 1, 1, 0}},   // 20 -> t
        {'u',  {1, 0, 0, 0, 1, 1}},   // 21 -> u
        {'v',  {1, 0, 1, 0, 1, 1}},   // 22 -> v
        {'w',  {0, 1, 1, 1, 0, 1}},   // 23 -> w
        {'x',  {1, 1, 0, 0, 1, 1}},   // 24 -> x
        {'y',  {1, 1, 0, 1, 1, 1}},   // 25 -> y
        {'z',  {1, 0, 0, 1, 1, 1}},   // 26 -> z
        {',',  {0, 0, 1, 0, 0, 0}},   // 27 -> ,
        {'.',  {0, 0, 1, 1, 0, 1}},   // 28 -> .
        {'?',  {0, 0, 1, 0, 1, 1}},   // 29 -> ?
        {'!',  {0, 0, 1, 1, 1, 0}},   // 30 -> !
        {':',  {0, 0, 1, 1, 0, 0}},   // 31 -> :
        {';',  {0, 0, 1, 0, 1, 0}},   // 32 -> ;
        {'\'', {0, 0, 0, 0, 1, 0}},  // 33 -> '
        {'\n', {0, 0, 0, 0, 0, 0}},  // 34 -> endLine
        {'D',  {0, 1, 0, 1, 1, 1}},   // 35 -> digit prefix
        {'E',  {1, 1, 1, 1, 1, 1}},   // 36 -> digit prefix
};


#endif
