objects = main.o
interfaces = common.h
CC = gcc
CFLAGS = -Wall -pedantic


yarco : $(objects)
	$(CC) $(CFLAGS) $< -o $@

$(objects): %.o: %.c common.h
#	$(CC) -c $(CFLAGS) $< -o $@

#main.o : common.h

$(interfaces) : %.h :  


.PHONY : clean
clean : 
	rm -f $(objects) yarco

