
AR ?= ar
CC ?= gcc
PREFIX ?= /usr/local

CFLAGS = -O3 -std=c99 -Wall -Wextra -Ideps

SRCS = src/list.c \
		   src/list_node.c \
		   src/list_iterator.c

OBJS = $(SRCS:.c=.o)

all: build/liblist.a build/liblist.so.1

install: all
	test -d $(PREFIX)/lib || mkdir -p $(PREFIX)/lib
	cp -f build/liblist.a $(PREFIX)/lib/liblist.a
	cp -f build/liblist.so.1 $(PREFIX)/lib/liblist.so.0.1.0
	ln -s liblist.so.0.1.0 $(PREFIX)/lib/liblist.so.1
	ln -s liblist.so.1 $(PREFIX)/lib/liblist.so
	test -d $(PREFIX)/include || mkdir -p $(PREFIX)/include/
	cp -f src/list.h $(PREFIX)/include/list.h

uninstall:
	rm -f $(PREFIX)/lib/liblist.a
	rm -f $(PREFIX)/include/list.h

build/liblist.a: $(OBJS)
	@mkdir -p build
	$(AR) rcs $@ $^

build/liblist.so.1: $(OBJS)
	@mkdir -p build
	ld -z now -shared -lc -soname `basename $@` src/*.o -o $@
	strip --strip-unneeded --remove-section=.comment --remove-section=.note $@

bin/test: test.o $(OBJS)
	@mkdir -p bin
	$(CC) $^ -o $@

bin/benchmark: benchmark.o $(OBJS)
	@mkdir -p bin
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr bin build *.o src/*.o

test: bin/test
	@./$<

benchmark: bin/benchmark
	@./$<

.PHONY: test benchmark clean install uninstall
