VPATH = ./lib/
objects =   physics.o graphics.o common.o graphics_terminal.o object.o person.o persontable.o
objectmain = main.o
objecttest = tests.o
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99


yarco :      $(objects) $(objectmain)
	$(CC) $(CFLAGS) $(objects) $(objectmain) -lm -o $@


yarco.test : $(objects) $(objecttest)
	$(CC) $(CFLAGS) $(objects) $(objecttest) -lm -o $@

main.o :        common.h
tests.o :       common.h
common.o :      common.h common.c
physics.o :     common.h physics.h object.h physics.c
graphics.o :    common.h graphics.h graphics.c
object.o :      common.h object.h object.c
person.o :      common.h object.h person.h
persontable.o : common.h persontable.h object.h person.h physics.h persontable.c
graphics_terminal.o : graphics.h common.h persontable.h person.h graphics_terminal.c

.PHONY : believe
believe : 
	@echo I won\'t play with you.

.PHONY : sandwich
sandwich :
	@echo Do it yourself.

.PHONY : clean
clean : 
	rm -f $(objects) $(objectmain) $(objecttest) yarco* #yarco.exe

.PHONY : moreclean
moreclean : clean
	rm -f autoTODO.txt \#*\# *~

.PHONY : TODO
TODO : 
	grep TODO *.[ch] lib/*.[ch] > autoTODO.txt