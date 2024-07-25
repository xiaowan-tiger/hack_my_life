ENV=../env
LDDIR=-L$(ENV)
LDLIBS=$(LDDIR) -lapue
LIBAPUE=../env/libapue.a
CFLAGS=-ansi -I$(ENV) -Wall -DLINUX -D_GNU_SOURCE $(EXTRA)
CC=gcc
PROGS = mycat

all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o

