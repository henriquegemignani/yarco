VPATH = ./lib/
objects =   physics.o graphics.o common.o object.o person.o persontable.o configuration.o class.o
objectmain = main.o
objecttest = tests.o
CC = gcc
CFLAGS = -Wall #-g #-pedantic -ansi # -std=c99


yarco :      $(objects) $(objectmain)
	$(CC) $(CFLAGS) `allegro-config --libs` $(objects) $(objectmain) -lm -o $@   #-lalleg  


yarco.test : $(objects) $(objecttest)
	$(CC) $(CFLAGS) $(objects) $(objecttest) -lm -o $@

main.o :        common.h
tests.o :       common.h
common.o :      common.h common.c
physics.o :     common.h physics.h object.h physics.c
object.o :      common.h object.h object.c
person.o :      common.h object.h person.h
persontable.o : common.h persontable.h object.h class.h person.h physics.h persontable.c
graphics.o :    common.h persontable.h graphics.h person.h graphics.c
#	$(CC) $(CFLAGS) -c -o $@ $(VPATH)graphics.c `allegro-config --libs` # -lalleg 
configuration.o: common.h configuration.h configuration.c
class.o :       common.h class.h object.h person.h class.c

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
