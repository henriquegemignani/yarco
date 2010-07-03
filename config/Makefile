objects = config_flex.o config_bison.o values.o ../lib/common.o
CFLAGS = -g -pedantic -ansi
CC = gcc

exec_config    : config_flex.o config_bison.o values.o
	$(CC) $(CFLAGS) $(objects) -lfl -o $@

config_flex.o  : config_flex.c config_bison.c
config_bison.o : config_bison.c

config_flex.c  : config.l
	flex -o config_flex.c config.l

config_bison.c : config.y
	bison -o config_bison.c -d config.y
	
values.o : configuration.h ../lib/common.o

.PHONY: clean
clean   :
	rm $(objects) config_flex.c config_bison.c config_bison.h exec_config
