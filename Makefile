VPATH = ./lib/
objects = main.o physics.o graphics.o common.o graphics_terminal.o persontable.o 
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99


yarco : $(objects)
	$(CC) $(CFLAGS) $(objects)-lm -o $@


main.o : common.h
common.o : common.h common.c
physics.o : physics.h common.h physics.c
graphics.o : common.h graphics.h graphics.c
persontable.o : persontable.h person.h persontable.c
graphics_terminal.o : graphics.h common.h persontable.h graphics_terminal.c


.PHONY : believe
believe : 
	echo I won\'t play with you.

.PHONY : clean
clean : 
	rm -f $(objects) yarco

.PHONY : moreclean
moreclean : clean
	rm -f \#*\# *~

