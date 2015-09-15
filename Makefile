### Makefile for gen-passwd ###
PROG=gen-passwd

PREFIX=/usr/local

OBJS=main.o args.o
LIBS=args.h alphabets.h

CFLAGS=-O2 -pipe -fstack-protector -Wl,-z,relro -Wl,-z,now -Wl,-O1 \
       -fno-exceptions
CC=gcc

all: $(PROG)

debug: CFLAGS+=-g -Wall -Wextra -pedantic -Wfloat-equal -Wundef \
               -Wshadow -Wpointer-arith -Wcast-align \
               -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings \
               -Waggregate-return -Wcast-qual -Wswitch-default \
               -Wswitch-enum -Wconversion -Wunreachable-code -Werror \
               -Wformat-security -Wformat-nonliteral
debug: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(LIBS)
	$(CC) $(CFLAGS) -c $<

.PHONY: clean install

clean:
	rm -f *.o $(PROG)

install:
	install -m 0755 $(PROG) $(PREFIX)/bin
	gzip gen-passwd.1
	chown root gen-passwd.1.gz
	chmod 644 gen-passwd.1.gz
	cp gen-passwd.1.gz /usr/share/man/man1

uninstall:
	rm -f $(PREFIX)/bin/$(PROG)
