# Makefile for 'Common' library
#
# Adwiteeya Paul (arp), May 14. 2025

OBJS = word.o pagedir.o index.o ../libcs50/bag.o ../libcs50/hash.o ../libcs50/webpage.o ../libcs50/mem.o ../libcs50/file.o  ../libcs50/libcs50-given.a 
LIBS = common.a

# uncomment the following to turn on verbose memory logging

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

$(LIBS): $(OBJS)
	ar cr $(LIBS) $(OBJS)

all: $(LIBS)

../libcs50/bag.o: ../libcs50/bag.h
../libcs50/hash.o: ../libcs50/hash.h
../libcs50/webpage.o: ../libcs50/webpage.h
../libcs50/file.o: ../libcs50/file.h
../libcs50/mem.o: ../libcs50/mem.h
../common/pagedir.o: ../common/pagedir.h
word.o: word.h 
pagedir.o: ../libcs50/webpage.h ../libcs50/file.h pagedir.h
index.o: index.h word.h ../libcs50/webpage.h ../libcs50/file.h




clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
	rm -f $(LIB) *~ *.o
