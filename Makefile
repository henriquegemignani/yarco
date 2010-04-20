objects = main.o
CC = gcc
CFLAGS = -Wall -pedantic


yarco : $(objects)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean: 
	rm -f $(objects) yarco