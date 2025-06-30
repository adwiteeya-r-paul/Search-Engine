#!/bin/bash
#test script for crawler.c
#adwiteeya rupantee paul
#5/7/25
#pass three command line arguments: seedURL, pageDirectory and maxDepth

# zero arguments                                                              
./crawler
# one argument                                                                      
./crawler http://cs50tse.cs.dartmouth.edu/tse/
# two arguments                                                                     
./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../testdirectory1
# invalid URL                                                    
./crawler http:// ../testdirectory1 0
# invalid pageDirectory
./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../datadata 0
# maxDepth out of range
./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../testdirectory1 100
# maxDepth out of range
./crawler http://cs50tse.cs.dartmouth.edu/tse/ ../testdirectory1 -1
# crawling letters till depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory1 0
# crawling letters till depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory1 1
# crawling letters till depth 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory1 10
# crawling toscrape till depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../testdirectory1 0
# crawling toscrape till depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../testdirectory1 1
#crawling wikipedia till depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../testdirectory1 0
#crawling wikipedia till depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../testdirectory1 1
# Valgrind with letters 0
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory1 0
# Valgrind with letters 1
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../testdirectory1 1
