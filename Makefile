objects = main.o common.o physics.o
libs = ./lib/
headers = ./lib/
CC = gcc
CFLAGS = -Wall -pedantic -ansi


yarco : $(objects)
	$(CC) $(CFLAGS) $< -o $@


main.o : $(headers)common.h
common.o : $(libs)common.c $(headers)common.h
	$(CC) $(CFLAGS) $(libs)common.c -c -lm -o $@
physics.o : $(headers)physics.h $(headers)common.h
	$(CC) $(CFLAGS) $(libs)physics.c -c -lm -o $@

.PHONY : believe
believe : 
	echo I won\'t play with you.

.PHONY : clean
clean : 
	rm -f $(objects) yarco


#interfaces = common.h
#sources = common.c

#$(interfaces) : %.h :
#$(sources) : %.c :   

#$(objects): %.o: %.c common.h

#common.o : 
#	$(CC) -c $(CFLAGS) $< -o $@