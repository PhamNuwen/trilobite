CC = gcc
LD = gcc
CFLAGS = -g -Wall -Iinclude
LFLAGS =
SRC = src
INCLUDE = include
AR = ar ruv

atom.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/atom.c
exception.o :
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/exception.c 
assert.o :
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/assert.c 
mem.o :
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/mem.c 
arena.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/arena.c 
list.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/list.c 
table.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/table.c

OBJS = atom.o\
	exception.o\
	assert.o\
	mem.o\
	arena.o\
	list.o\
	table.o


trilib::	$(OBJS)
	$(AR) $@.a $(OBJS)

clean::
	rm -f *.o

test::		trilib
	$(CC) $(CFLAGS) -c -o test_main.o tst/test_main.c
	$(LD) ${LFLAGS} -o $@ test_main.o trilib.a