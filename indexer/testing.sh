#!/bin/bash
#test script for indexer.c
#adwiteeya rupantee paul
#5/14/25
#pass three command line arguments: ../data and test
#the tests with indexests have been done separately with testing mode on as otherwise there are 2 mains, and then the results have been added

# zero arguments                                                              
./indexer
# one argument                                                                      
./indexer ../testdirectory1
# three or more arguments                                                                     
./indexer ../testdirectory1 ../testdirectory1 ../testdirectory1
# invalid pageDirectory                                                  
./indexer testdirectory1
# invalid pageDirectory (not a crawler directory)
./indexer ../common
# invalid indexFile
./indexer hello
# invalid indexFile (read-only directory)
./indexer ../testdirectory3 testfile3
# invalid indexFile (read-only)
./indexer ../testdirectory1 ../testdirectory3/file
# indexer on different pageDirectories 
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory2 2)
./indexer ../testdirectory2 testfile1
# Indextest on direct
./indextest testfile1 testfile2
# matching with indexcmp
~/cs50-dev/shared/tse/indexcmp testfile1 testfile2
# Indextest on data
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../data 1)
./indexer ../testdirectory1 testfile3
# Indextest on data
./indextest testfile1 testfile2
# matching indexer on data
~/cs50-dev/shared/tse/indexcmp testfile1 testfile2
# Valgrind with indexer
valgrind ./indexer ../testdirectory1 testfile3
# Valgrind with indextest
valgrind ./indextest ../testdirectory/1 testfile4
