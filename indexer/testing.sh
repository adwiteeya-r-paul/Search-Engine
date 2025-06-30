#!/bin/bash
#test script for indexer.c
#adwiteeya rupantee paul
#5/14/25
#pass three command line arguments: ../data and test
#the tests with indexests have been done separately with testing mode on as otherwise there are 2 mains, and then the results have been added

# zero arguments                                                              
./indexer
# one argument                                                                      
./indexer ../data
# three or more arguments                                                                     
./indexer ../data ../data ../data
# invalid pageDirectory                                                  
./indexer data
# invalid pageDirectory (not a crawler directory)
./indexer ../common
# invalid indexFile
./indexer hello
# invalid indexFile (read-only directory)
./indexer ../directory test
# invalid indexFile (read-only)
./indexer ../data ../directory/file
# indexer on different pageDirectories 
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../direct 2)
./indexer ../direct file
# Indextest on direct
./indextest file file2
# matching with indexcmp
~/cs50-dev/shared/tse/indexcmp file file2
# Indextest on data
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../data 1)
./indexer ../data test
# Indextest on data
./indextest file file2
# matching indexer on data
~/cs50-dev/shared/tse/indexcmp file file2
# Valgrind with indexer
valgrind ./indexer ../data test
# Valgrind with indextest
valgrind ./indextest ../data/1 testy