CC = gcc
LD = gcc
CFLAGS = -g -Wall -Iinclude
LFLAGS =
SRC = src
INCLUDE = include
AR = ar ruv

exception.o :
	$(CC) $(CFLAGS) -c -o $@ $(SRC)/exception.c 

OBJS = exception.o


trilib::	$(OBJS)
	$(AR) $@.a $(OBJS)

clean::
	rm -f *.o

test::		trilib
	$(CC) $(CFLAGS) -c -o test_main.o tst/test_main.c
	$(LD) ${LFLAGS} -o $@ test_main.o trilib.a