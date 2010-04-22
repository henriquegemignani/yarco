VPATH = ./lib/
objects = main.o physics.o graphics.o common.o graphics_terminal.o object.o person.o persontable.o
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99


yarco : $(objects)
	$(CC) $(CFLAGS) $(objects) -lm -o $@


main.o :        common.h
common.o :      common.h common.c
physics.o :     common.h physics.h physics.c
graphics.o :    common.h graphics.h graphics.c
object.o :	common.h object.h object.c
person.o :      common.h object.h person.h
persontable.o : common.h persontable.h person.h persontable.c
graphics_terminal.o : graphics.h common.h persontable.h person.h graphics_terminal.c


.PHONY : believe
believe : 
	echo I won\'t play with you.

.PHONY : clean
clean : 
	rm -f $(objects) yarco

.PHONY : moreclean
moreclean : clean
	rm -f \#*\# *~

