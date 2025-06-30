## Adwiteeya Paul (arp), May 23, 2025

# Errors

Initially I had `14,000` bytes of memory leak, now I have `8` bytes (Couldn't get it lower than this).  

My querier does not prompt the user for a new query. 

I implemented these 3 functionalities: 

1.querier prints the set of documents that contain all the words in the query
2.querier also supports 'and' and 'or' operators, but without precedence (in mathematical terms, it treats them as left associative, equal precedence operators).
3.querier also supports 'and' precedence over 'or'.

My testing is a short bash script and some other commands.
Some commands that test edge cases, although worked before, now might show core dump. 

### indexer
The TSE Querier is a standalone program that reads the index file produced by the TSE Indexer, and page files produced by the TSE Querier, and answers search queries submitted via stdin.

The querier shall:

execute from a command line with usage syntax

./querier pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where indexFilename is the pathname of a file produced by the Indexer.
validate it received exactly two command-line arguments and that

pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be read;
load the index from indexFilename into an internal data structure.

read search queries from stdin, one per line, until EOF.

clean and parse each query according to the syntax described below.
if the query syntax is somehow invalid, print an error message, do not perform the query, and prompt for the next query.
print the 'clean' query for user to see.
use the index to identify the set of documents that satisfy the query, as described below.
if the query is empty (no words), print nothing.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
output nothing to stdout other than what is indicated above

exit zero when EOF is reached on stdin; exit with an error message to stderr and non-zero exit status on encountering an unrecoverable error, including

out of memory,
invalid command-line arguments,
unable to read a file named pageDirectory/.crawler,
unable to read a file named pageDirectory/1
unable to read a file named indexFilename




### Usage

The *querier* module, defined in `querier.h` and implemented in `querier.c`, implements a querier, and exports the following function:

```c
int main(int argc, char* argv[]);
void parse_query(index_t* index, char* pageDirectory);
void verify_query(char* line, int length);
int tokenize_query(char* line, char* words[], int inputlength);
void bnf_query(char* words[], int inputlength);
void score_query(char* words[], int inputlength, char* pageDirectory, index_t* index);
void rank_query(counters_t* counter, char* Directory);
counters_t* and_query(index_t* index, char* word1, char* word2);
counters_t* or_query(index_t* index, char* word1, char* word2);
```


### Implementation


We implement this with the help of the data structure `index` built in `common`. `pagedir` and `word` modules are also used. Other than the above functions, there are some helper functions to help implement different query mergings and ranking, which are static and are present in the querier module. 

### Assumptions

pageDirectory has files named 1, 2, 3, ..., without gaps.
The content of files in pageDirectory follow the format as defined in the specs; thus your code (to read the files) need not have extensive error checking.
The content of the file named by indexFilename follows our index file format (as defined in Lab 5); thus your code (to recreate an index structure by reading a file) need not have extensive error checking.
The provided index file corresponds to the provided pageDirectory, that is, was built by indexer from the files in that directory.



### Files

* `Makefile` - compilation procedure
* `indexer.h` - the interface
* `indexer.c` - the implementation
* `indextest.c` - unit testing
* `testing.sh` - test script
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make indexer`.

### Testing

The `testing.sh`

To unit test, comment out `TESTING` in makefile. 

To integration test, comment out `make test` and do `make test`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
