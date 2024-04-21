CC=gcc
CFLAGS=-I.
DEPS = scheduler.h
OBJ = RR.o datasets.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

RR: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)