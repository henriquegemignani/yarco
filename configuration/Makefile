objects = config_flex.o config_bison.o
CFLAGS = 
CC = gcc

exec_config    : config_flex.o config_bison.o
	$(CC) $(CFLAGS) $(objects) -lfl -o $@

config_flex.o  : config_flex.c config_bison.c
config_bison.o : config_bison.c

config_flex.c  : config.l
	flex -o config_flex.c config.l

config_bison.c : config.y
	bison -o config_bison.c -d config.y

.PHONY: clean
clean   :
	rm $(objects) config_flex.c config_bison.c config_bison.h exec_config
