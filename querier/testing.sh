#!/bin/bash
#test script for querier.c
#adwiteeya rupantee paul
#5/23/25
#pass two command line arguments: pageDirectory and indexFile

# zero arguments                                                              
./querier
# one argument                                                                      
./querier ../direct 
# two arguments
./querier ../direct ../indexer/file
# three or more arguments                                                                     
./indexer ../data ../data ../data
# invalid pageDirectory                                                  
./querier data
# invalid pageDirectory (not a crawler directory)
./querier ../common
# invalid indexFile
./querier hello
# invalid indexFile (read-only directory)
./querier ../directory ../indexer/test
# invalid indexFile (read-only)
./querier ../directory ../directory/file
# querier on different pageDirectories 
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../direct 2)
./querier ../direct ../indexer/file
# created by: (./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../data 1)
./querier ../data ../indexer/file
# querier on different indexFiles
./querier ../data ../indexer/file
./querier ../data ../indexer/file2
# Indextest on direct
./indextest file ../indexer/file2
# Valgrind with querier
valgrind ./querier ../data/ ../indexer/file
# Valgrind with querier
valgrind ./querier ../data/ ../indexer/file2
