CC=gcc

CFLAGS= -Wall -g -c


all: main.o db_ops.o rw_ops.o help_functions.o
	$(CC) -o db main.o db_ops.o rw_ops.o help_functions.o
db_ops.0:db_ops.c
	$(CC) $(CFLAGS)  io_ops.c db_ops.h
rw_ops.0: rw_ops_c
	$(CC) $(CFLAGS) rw_ops.c 
help_functions.o: help_functions.c
	$(CC) $(CFLAGS) help_functions.c
clean:
	rm *.o db
