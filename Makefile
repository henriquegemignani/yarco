VPATH = ./lib/:./class/:./config/
objects = graphics.o common.o object.o person.o objecttable.o class.o ship.o coral.o boat.o vector.o config_flex.o config_bison.o values.o command_line.o logic.o report.o
objectmain = main.o
CC = gcc
CFLAGS = -Wall -g # -pedantic -ansi -D_POSIX_C_SOURCE=199309L
ifeq ($(shell uname), CYGWIN_NT-6.1-WOW64)
ALLEG = -LC:\MinGW\lib -lliballeg44
else
ALLEG = `allegro-config --libs`
endif

yarco :      $(objects) $(objectmain)
	$(CC) $(CFLAGS) -o $@ $(objects) $(objectmain) -lfl -lm $(ALLEG)

main.o :		common.h logic.h main.c
common.o :      common.h common.c
object.o :      common.h object.h vector.h object.c
graphics.o :    common.h object.h objecttable.h report.h graphics.h graphics.c
command_line.o: common.h configuration.h command_line.c
objecttable.o : common.h object.h class.h objecttable.h configuration.h objecttable.c
class.o :       common.h object.h class.h class.c
person.o :      common.h object.h class.h objecttable.h vector.h person.h person.c
ship.o :		common.h object.h class.h objecttable.h ship.h ship.c
coral.o :		common.h object.h class.h objecttable.h coral.h coral.c
boat.o :		common.h object.h class.h objecttable.h vector.h report.h boat.h boat.c
vector.o :		common.h vector.h vector.c
logic.o :		common.h object.h objecttable.h configuration.h graphics.h class.h person.h ship.h coral.h boat.h report.h logic.c
report.o :		common.h report.h report.c

values.o : 		common.h configuration.h values.c values_default.c

config_flex.o  : config_flex.c config_bison.c configuration.h
	$(CC) -c -o config_flex.o config/config_flex.c
config_bison.o : config_bison.c configuration.h
	$(CC) -c -o config_bison.o config/config_bison.c

config_flex.c  : config.l
	flex -oconfig/config_flex.c config/config.l
config_bison.c : config.y
	bison -o config/config_bison.c -d config/config.y

.PHONY : believe
believe : 
	@echo I won\'t play with you.

.PHONY : sandwich
sandwich :
	@echo Do it yourself.

.PHONY: cake
cake:
	@echo Cake not found.
	@echo Press any key to fill the room with a deadly neurotoxin.
	@sleep 5

.PHONY : clean
clean : 
	rm -f $(objects) $(objectmain) $(objecttest)

.PHONY : moreclean
moreclean : clean
	rm -f autoTODO.txt \#*\# *~ */\#*\# */*~ yarco*

.PHONY : realclean
realclean : moreclean
	rm -f config/config_*.[ch]
	rm -rf publish/
	
.PHONY : nuke
nuke :
ifeq ($(shell head -1 Makefile), VPATH = ./lib/:./class/:./config/)
	@echo Nuclear Launch Detected
	rm -rf ./
else
	@echo Sabotagem nuclear detectada, abortando missão.
endif

.PHONY : TODO
TODO : 
	grep TODO *.[ch] */* > autoTODO.txt

.PHONY: publish
publish : moreclean yarco
	mkdir -p publish
	rm -f publish/yarco.tar
	tar -cvzf publish/yarco.tar.gz yarco* --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish

.PHONY: publish-source
publish-source : realclean
	indent -i4 -kr -nut *.c */*.[ch]
	mkdir -p publish
	rm -f publish/source.tar
	tar -cvzf publish/source.tar.gz * --exclude=scripts --exclude=TODO.txt --exclude=.svn --exclude=publish\
	 --exclude=*~ --exclude=tests.c
