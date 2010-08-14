
CC = gcc
CFLAGS = -O3 -std=c99 -Wall

SRCS = src/list.c \
		   src/node.c \
		   src/iterator.c

OBJS = $(SRCS:.c=.o)

all: bin/test

bin/test: test.o $(OBJS)
	@mkdir -p bin
	$(CC) test.o $(OBJS) -o $@

bin/benchmark: benchmark.o $(OBJS)
	@mkdir -p bin
	$(CC) benchmark.o $(OBJS) -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr bin
	rm -f *.o
	rm -f src/*.o

test: bin/test
	@./$<

benchmark: bin/benchmark
	@./$<

.PHONY: test benchmark clean