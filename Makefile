
AR ?= ar
CC ?= gcc
STRIP ?= strip
PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
INCLUDEDIR ?= $(PREFIX)/include
INCLUDESUBDIR ?= /clibs
DESTDIR ?=

CFLAGS = -O3 -std=c99 -Wall -Wextra -Ideps
LDFLAGS ?= -Wl,-z,now

SRCS = src/list.c \
		   src/list_node.c \
		   src/list_iterator.c

OBJS = $(SRCS:.c=.o)

MAJOR_VERSION = 0
MINOR_VERSION = 2
PATCH_VERSION = 0

all: build/liblist.a build/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)

install: all
	test -d $(DESTDIR)$(LIBDIR) || mkdir -p $(DESTDIR)$(LIBDIR)
	cp -f build/liblist.a $(DESTDIR)$(LIBDIR)/liblist.a
	cp -f build/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)
	ln -sf liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION) $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION)
	ln -sf liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION) $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION)
	ln -sf liblist.so.$(MAJOR_VERSION) $(DESTDIR)$(LIBDIR)/liblist.so
	test -d $(DESTDIR)$(INCLUDEDIR)$(INCLUDESUBDIR) || mkdir -p $(DESTDIR)$(INCLUDEDIR)$(INCLUDESUBDIR)/
	cp -f src/list.h $(DESTDIR)$(INCLUDEDIR)$(INCLUDESUBDIR)/list.h

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/liblist.a
	rm -f $(DESTDIR)$(LIBDIR)/liblist.so
	rm -f $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION)
	rm -f $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION)
	rm -f $(DESTDIR)$(LIBDIR)/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION)
	rm -f $(DESTDIR)$(INCLUDEDIR)$(INCLUDESUBDIR)/list.h

build/liblist.a: $(OBJS)
	@mkdir -p build
	$(AR) rcs $@ $^

build/liblist.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(PATCH_VERSION): $(OBJS)
	@mkdir -p build
	$(CC) $(LDFLAGS) -shared -lc -Wl,-soname,`basename $@` src/*.o -o $@
	$(STRIP) --strip-unneeded --remove-section=.comment --remove-section=.note $@

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
