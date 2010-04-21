VPATH = ./lib/
objects = main.o physics.o graphics.o common.o 
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99


yarco : $(objects)
	$(CC) $(CFLAGS) $(objects)-lm -o $@


main.o : common.h
common.o : common.h common.c
physics.o : physics.h common.h physics.c
graphics.o : common.h graphics.h graphics.c


.PHONY : believe
believe : 
	echo I won\'t play with you.

.PHONY : clean
clean : 
	rm -f $(objects) yarco

.PHONY : moreclean
moreclean : clean
	rm -f \#*\# *~

