VPATH = ./lib/:./class/
objects =   physics.o graphics.o common.o object.o person.o objecttable.o configuration.o class.o ship.o  coral.o boat.o
objectmain = main.o
objecttest = tests.o
CC = gcc
CFLAGS = -Wall -g #-pedantic -ansi # -std=c99


yarco :      $(objects) $(objectmain)
	$(CC) $(CFLAGS) `allegro-config --libs` $(objects) $(objectmain) -lm -o $@   


yarco.test : $(objects) $(objecttest)
	$(CC) $(CFLAGS) $(objects) $(objecttest) -lm -o $@

main.o :        common.h coral.h ship.h class.h configuration.h graphics.h objecttable.h main.c
tests.o :       common.h
common.o :      common.h common.c
physics.o :     common.h physics.h object.h physics.c
object.o :      common.h object.h object.c
person.o :      common.h object.h person.h person.c
objecttable.o : common.h object.h objecttable.h class.h physics.h objecttable.c
graphics.o :    common.h object.h objecttable.h graphics.h graphics.c
configuration.o: common.h configuration.h configuration.c
class.o :       common.h object.h class.h objecttable.h class.c
ship.o :		common.h object.h class.h objecttable.h ship.h ship.c
coral.o :		common.h object.h class.h objecttable.h coral.h coral.c
boat.o :		common.h object.h class.h objecttable.h boat.h boat.c

.PHONY : believe
believe : 
	@echo I won\'t play with you.

.PHONY : sandwich
sandwich :
	@echo Do it yourself.

.PHONY : clean
clean : 
	rm -f $(objects) $(objectmain) $(objecttest) yarco*

.PHONY : moreclean
moreclean : clean
	rm -f autoTODO.txt \#*\# *~ lib/\#*\# lib/*~ 

.PHONY : realclean
realclean : moreclean
	rm -rf publish/

.PHONY : TODO
TODO : 
	grep TODO *.[ch] lib/*.[ch] > autoTODO.txt

.PHONY: publish
publish : moreclean yarco
	mkdir -p publish
	rm -f publish/yarco.tar
	tar -cvzf publish/yarco.tar.gz yarco* --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish

.PHONY: publish-source
publish-source : moreclean
	indent -i4 -kr -nut *.c lib/*.[ch]
	mkdir -p publish
	rm -f publish/source.tar
	tar -cvzf publish/source.tar.gz * --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish --exclude=*~
