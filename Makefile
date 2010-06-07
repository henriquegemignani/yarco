VPATH = ./lib/:./class/
objects = graphics.o common.o object.o person.o objecttable.o configuration.o class.o ship.o coral.o boat.o vector.o
objectmain = main.o
objecttest = tests.o
CC = gcc
CFLAGS = -Wall -g -pedantic -ansi -D_POSIX_C_SOURCE=199309L

yarco :      $(objects) $(objectmain)
	$(CC) $(CFLAGS) `allegro-config --libs` $(objects) $(objectmain) -lm -o $@   


yarco.test : $(objects) $(objecttest)
	$(CC) $(CFLAGS) $(objects) $(objecttest) -lm -o $@

main.o :        common.h coral.h ship.h class.h configuration.h graphics.h objecttable.h main.c
tests.o :       common.h
common.o :      common.h common.c
object.o :      common.h object.h object.c
person.o :      common.h object.h person.h person.c
objecttable.o : common.h object.h objecttable.h class.h objecttable.c
graphics.o :    common.h object.h objecttable.h graphics.h graphics.c
configuration.o: common.h configuration.h configuration.c
class.o :       common.h object.h class.h objecttable.h class.c
ship.o :		common.h object.h class.h objecttable.h ship.h ship.c
coral.o :		common.h object.h class.h objecttable.h coral.h coral.c
boat.o :		common.h object.h class.h objecttable.h boat.h boat.c
vector.o :		common.h vector.h vector.c

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
	rm -f autoTODO.txt \#*\# *~ lib/\#*\# lib/*~ class/\#*\# class/*~ 

.PHONY : realclean
realclean : moreclean
	rm -rf publish/

.PHONY : TODO
TODO : 
	grep TODO *.[ch] lib/*.[ch] class/*.[ch] > autoTODO.txt

.PHONY: publish
publish : moreclean yarco
	mkdir -p publish
	rm -f publish/yarco.tar
	tar -cvzf publish/yarco.tar.gz yarco* --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish

.PHONY: publish-source
publish-source : moreclean
	indent -i4 -kr -nut *.c lib/*.[ch] class/*.[ch]
	mkdir -p publish
	rm -f publish/source.tar
	tar -cvzf publish/source.tar.gz * --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish --exclude=*~
