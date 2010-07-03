objects = config_flex.o config_bison.o values.o common.o command_line.o
CFLAGS = -g -pedantic -ansi
CC = gcc

exec_config    : $(objects)
	$(CC) $(CFLAGS) $(objects) -lfl -o $@

config_flex.o  : config_flex.c config_bison.c configuration.h
config_bison.o : config_bison.c configuration.h
values.o : configuration.h common.o
command_line.o: configuration.h command_line.c

common.o : ../lib/common.h
	$(CC) -c -o common.o ../lib/common.c

config_flex.c  : config.l
	flex -o config_flex.c config.l

config_bison.c : config.y
	bison -o config_bison.c -d config.y

.PHONY: clean
clean   :
	rm $(objects) config_flex.c config_bison.c config_bison.h exec_config
