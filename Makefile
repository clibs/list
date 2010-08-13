
CC = gcc
SRCS = src/list.c \
		   src/test.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -std=c99

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