VPATH = ./lib/
objects =   physics.o graphics.o common.o graphics_terminal.o object.o person.o persontable.o configuration.o
objectmain = main.o
objecttest = tests.o
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99 #-g


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
configuration.o: common.h configuration.h configuration.c

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
	rm -f autoTODO.txt \#*\# *~ lib/\#*\# lib/*~ 

.PHONY : TODO
TODO : 
	grep TODO *.[ch] lib/*.[ch] > autoTODO.txt
    
.PHONY: publish
publish : moreclean yarco
	mkdir -p publish
	rm -f publish/yarco.tar
	tar -cvf publish/yarco.tar yarco* --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish
    
.PHONY: publish-source
publish-source : moreclean
	mkdir -p publish
	rm -f publish/source.tar
	tar -cvf publish/source.tar * --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish
