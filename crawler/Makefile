# Makefile for crawler module
# Adwiteeya Paul (arp), May 7. 2025


OBJS = crawler.o ../libcs50/bag.o ../libcs50/hash.o ../libcs50/webpage.o ../libcs50/mem.o ../libcs50/file.o ../common/pagedir.o ../libcs50/libcs50-given.a
LIBS =

# uncomment the following to turn on verbose memory logging
TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all


crawler: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: crawler.c
	$(CC) $(CFLAGS) $^ -c -o $@

../libcs50/bag.o: ../libcs50/bag.h
../libcs50/hash.o: ../libcs50/hash.h
../libcs50/webpage.o: ../libcs50/webpage.h
../libcs50/file.o: ../libcs50/file.h
../common/pagedir.o: ../common/pagedir.h

.PHONY: test valgrind clean

# expects a file `testing.sh` to exist; it can contain any text.
test: crawler testing.sh
	./crawler < testing.sh &> testing.out

# expects a file `testing.sh` to exist; it can contain any text.
valgrind: crawler testing.sh
	$(VALGRIND) ./crawler < testing.sh &> testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f crawler
