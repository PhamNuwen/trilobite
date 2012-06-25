CC = gcc
LD = gcc
CFLAGS = -g -Wall -Iinclude -std=c99
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
arith.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/arith.c
set.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/set.c
array.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/array.c
seq.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/seq.c
fmt.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/fmt.c
chan.o:
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/chan.c


OBJS = atom.o\
	exception.o\
	assert.o\
	mem.o\
	arena.o\
	list.o\
	table.o\
	arith.o\
	set.o\
	array.o\
	seq.o\
	fmt.o

all::		$(OBJS)
	$(AR) $@.a $(OBJS)

trilib::	$(OBJS)
	$(AR) $@.a $(OBJS)

clean::
	rm -f *.o
	rm -f *.a

test::		trilib
	$(CC) $(CFLAGS) -c -o test_main.o tst/test_main.c
	$(LD) ${LFLAGS} -o $@ test_main.o trilib.a
