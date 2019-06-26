CC      = gcc
CFLAGS  = -Wall -std=c11 -g -pedantic
LDLIBS  = -lwiringPi
BUILD   = translate

all: $(BUILD)
clean:
	/bin/rm -f $(BUILD) *.o core

translate:	translate.o ledMatrix.o motorControl.o buttonControl.o

translate.o:	translate.h ledMatrix.h motorControl.h buttonControl.h

ledMatrix.o:	ledMatrix.h

motorControl.o:	motorControl.h

buttonControl.o:	buttonControl.h

motorControl.h:	structs.h

buttonControl.h:	structs.h

translate.h:	structs.h

.PHONY: clean
.SUFFIXES: .c .o 
