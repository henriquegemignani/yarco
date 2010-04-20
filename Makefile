objects = 
CC = gcc
CFLAGS = -Wall -pedantic


yarco : ${objects}
	{CC} $(objects} -o $@