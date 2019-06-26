#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <wiringPi.h>
#include "translate.h"
#include "ledMatrix.h"
#include "motorControl.h"
#include "buttonControl.h"

#define DIGIT_DIVISION_CONST 2

brailleEncoding get_special(char c) {
    const int alphabet_size = 26;
    const int special_char_size = 8;
    for (int i = alphabet_size; i < alphabet_size + special_char_size; i++) {
        if (table[i].symbol == c)
            return table[i];
    }
    return table[EMPTY];
}


int compare_pins(brailleEncoding first, brailleEncoding second) {
    for (int i = 0; i < 6; i++) {
        if (first.pins[i] != second.pins[i])
            return false;
    }
    return true;
}

int braille_to_output(brailleEncoding encoding, bool isDigit) {
    for (int i = 0; i < 37; i++) {
        if (compare_pins(table[i], encoding)) {
            if (table[i].symbol == 'E') {
                return false;
            }
            if (table[i].symbol == 'D') {
                return braille_to_output(readChar(), true);
            }
            if (isDigit) {
                char digit = table[i].symbol - 'a' + '1';
                if (digit > '9') {
                    digit -= 10;
                }
                printf("%c", digit);
            } else {
                printf("%c", table[i].symbol);
            }
            fflush(stdout);
            return true;
        }
    }
    return false;
}


void print(struct brailleEncoding braille, const int time) {
    bool matrix[N_OF_ROWS][N_OF_COLS];

    setMatrix(matrix, braille);

    //printf("%c\n", braille.symbol);
    printf("%d%d\n%d%d\n%d%d", braille.pins[0], braille.pins[1],
           braille.pins[2], braille.pins[3], braille.pins[4], braille.pins[5]);
    printf("\n-------\n");

    execute_instruction(braille);

    turn_on(matrix, time);

    stop_all();
}

void setMatrix(bool matrix[N_OF_ROWS][N_OF_COLS], brailleEncoding braille) {
    int x = 0;
    for (int i = 0; i < N_OF_ROWS; i++) {
        for (int j = 0; j < N_OF_COLS; j++) {
            matrix[i][j] = braille.pins[x];
            x++;
        }
    }
}

void init() {
    wiringPiSetup();

    init_led();

    init_motors();

    init_buttons();
}

void process_character(char c, const int time) {
    brailleEncoding braille;
    if (isalpha(c)) {
        c = tolower(c);
        printf("%c\n", c);
        braille = table[c - 'a' + 1];
    } else if (isdigit(c)) {
        printf("Digit symbol\n");
        print(table[DIGIT], time / DIGIT_DIVISION_CONST);
        printf("%c\n", c);
        braille = c == '0' ? table[c - '1' + 11] : table[c - '1' + 1];
    } else {
        braille = get_special(c);
    }

    print(braille, time);

}

int main(int argc, char **argv) {

    const int seconds_to_millis_mult = 1000;
    const int file_path_size = 256;


    init();

    int type;
    double timeSeconds = -1;
    int time;

    do {
        type = 3;
        printf("Select type:\n 1.Text to Braille\n 2.Braille to text\n else: exit\n");
        scanf("%d", &type);


        if (type == 1) {
            if (timeSeconds == -1) {
                printf("Input your desired reading speed in seconds:\n");
                scanf("%lf", &timeSeconds);
                time = timeSeconds * seconds_to_millis_mult;
            }

            printf("Choose which way you want to send the message in:\n 1. Read from a file\n 2. Read from input\n");
            int a;
            scanf("%d", &a);

            if (a == 1) {
                printf("Input the path to the file:\n");

                char filePath[file_path_size];
                scanf("%s", filePath);

                FILE *read_file = fopen(filePath, "r");

                if (read_file == NULL) {
                    exit(EXIT_FAILURE); // TODO
                }

                char c;
                while (!feof(read_file)) {
                    c = fgetc(read_file);
                    process_character(c, time);
                }
                fclose(read_file);


            } else if (a == 2) {
                printf("Type the string you want to translate into Braille\n");
                char nonBrailleString[file_path_size];
                scanf("%s", nonBrailleString);

                for (int i = 0; nonBrailleString[i] != '\0'; i++) {
                    process_character(nonBrailleString[i], time);
                }

            }
        } else if (type == 2) {
            brailleEncoding c = readChar();
            for (;;) {
                if (!braille_to_output(c, false)) {
                    printf("\n");
                    break;
                }
                c = readChar();
            }
        }
    } while (type == 1 || type == 2);
    return EXIT_SUCCESS;
}
