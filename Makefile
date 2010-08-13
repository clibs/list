
CC = gcc
CFLAGS = -std=c99 -Wall

SRCS = src/list.c \
		   src/node.c \
		   src/iterator.c \
		   src/test.c

OBJS = $(SRCS:.c=.o)

all: bin/test

bin/test: $(OBJS)
	@mkdir -p bin
	$(CC) $(OBJS) -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr bin
	rm src/*.o

test: bin/test
	@./bin/test

.PHONY: test clean