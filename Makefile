CC=gcc

CFLAGS= -c

all: main.o io_ops.o rw_ops.o
	$(CC) -o db main.o io_ops.o rw_ops.o
io_ops.0:io_ops.c  db_ops.h
	$(CC) $(CFLAGS)  io_ops.c db_ops.h
rw_ops.0: rw_ops_c db_ops.h
	$(CC) $(CFLAGS) rw_ops.c db_ops.h 

clean:
	rm *.o db
