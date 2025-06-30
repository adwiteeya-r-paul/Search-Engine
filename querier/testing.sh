#!/bin/bash
#test script for querier.c
#adwiteeya rupantee paul
#5/23/25
#pass two command line arguments: pageDirectory and indexFile

# zero arguments                                                              
./querier
# one argument                                                                      
./querier ../testdirectory2 
# two arguments
./querier ../testdirectory2 ../indexer/testfile1
# three or more arguments                                                                     
./indexer ../testdirectory1 ../testdirectory1 ../testdirectory1
# invalid pageDirectory                                                  
./querier testdirectory1
# invalid pageDirectory (not a crawler directory)
./querier ../common
# invalid indexFile
./querier hello
# invalid indexFile (read-only directory)
./querier ../testdirectory3 ../indexer/testfile3
# invalid indexFile (read-only)
./querier ../testdirectory3 ../testdirectory3/testfile1
# querier on different pageDirectories 
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory2 2)
./querier ../testdirectory2 ../indexer/testfile1
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../testdirectory1 1)
./querier ../testdirectory1 ../indexer/testfile1
# querier on different indexFiles
./querier ../testdirectory1 ../indexer/testfile1
./querier ../testdirectory1 ../indexer/testfile2
# Indextest on testdirectory2
./indextest testfile1 ../indexer/testfile2
# Valgrind with querier
valgrind ./querier ../testdirectory1 ../indexer/testfile1
# Valgrind with querier
valgrind ./querier ../testdirectory1 ../indexer/testfile2
