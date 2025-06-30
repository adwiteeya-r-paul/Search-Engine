# Makefile for crawler module
# Adwiteeya Paul (arp), May 7. 2025


OBJS = querier.o ../libcs50/bag.o ../libcs50/hash.o ../libcs50/webpage.o ../libcs50/mem.o ../libcs50/file.o ../common/index.o ../common/pagedir.o ../common/word.o ../libcs50/libcs50-given.a
LIBS =

# uncomment the following to turn on testing
#TESTING = -DTESTING

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all




querier: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o: querier.c
	$(CC) $(CFLAGS) $^ -c -o $@


../libcs50/bag.o: ../libcs50/bag.h
../libcs50/hash.o: ../libcs50/hash.h
../libcs50/webpage.o: ../libcs50/webpage.h
../libcs50/file.o: ../libcs50/file.h
../common/index.o: ../common/index.h
../common/pagedir.o: ../common/pagedir.h
../common/word.o: ../common/word.h


.PHONY: test valgrind clean

# expects a file `testing.sh` to exist; it can contain any text.
#test: indexer testing.sh
#bash -v testing.sh
#uncomment for integration testing

	
# expects a file `testing.sh` to exist; it can contain any text.
valgrind: querier testing.sh
	$(VALGRIND) ./querier < testing.sh &> testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f querier
