objects = main.o common.o physics.o graphics.o
libs = ./lib/
headers = ./lib/
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99


yarco : $(objects)
	$(CC) $(CFLAGS) $< -o $@


main.o : $(headers)common.h
common.o : $(headers)common.h
	$(CC) $(CFLAGS) $(libs)common.c -c -lm -o $@
physics.o : $(headers)physics.h $(headers)common.h
	$(CC) $(CFLAGS) $(libs)physics.c -c -lm -o $@
graphics.o : $(headers)common.h $(headers)graphics.h

.PHONY : believe
believe : 
	echo I won\'t play with you.

.PHONY : clean
clean : 
	rm -f $(objects) yarco

.PHONY : moreclean
moreclean : clean
	rm -f \#*\# *~


#interfaces = common.h
#sources = common.c

#$(interfaces) : %.h :
#$(sources) : %.c :   

#$(objects): %.o: %.c common.h

#common.o : 
#	$(CC) -c $(CFLAGS) $< -o $@