## Adwiteeya Paul (arp), May 14, 2025

### indexer
The TSE `indexer` is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the `index tester`, loads an index file produced by the indexer and saves it to another file.

The `indexer` shall:

execute from a command line with usage syntax

./indexer pageDirectory indexFilename
where pageDirectory is the pathname of a directory produced by the Crawler, and
where `indexFilename` is the pathname of a file into which the index should be written; the indexer creates the file (if needed) and overwrites the file (if it already exists).
validate it received exactly two command-line arguments and that

pageDirectory is the pathname for a directory produced by the Crawler, and
indexFilename is the pathname of a file that can be written;
read documents from the pageDirectory, each of which has a unique document ID, wherein

the document id starts at 1 and increments by 1 for each new page,
and the filename is of form pageDirectory/id,
and the first line of the file is the URL,
and the second line of the file is the depth,
and the rest of the file is the page content (the HTML, unchanged).
build an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and `normalize` the word before indexing. (Here, "normalize" means to convert all letters to lower-case.)

create a file `indexFilename` and write the index to that file, in the format described below.

output nothing to stdout

exit zero if successful; exit with an error message to stderr and non-zero exit status on encountering an unrecoverable error, including

out of memory,
invalid command-line arguments,
unable to read a file named pageDirectory/.crawler,
unable to read a file named pageDirectory/1
unable to write a file named indexFilename
The indexer may assume that

pageDirectory has files named 1, 2, 3, ..., without gaps.
The content of files in `pageDirectory` follow the format as defined in the specs; thus your code (to read the files) need not have extensive error checking.


### Usage

The *indexer* module, defined in `indexer.h` and implemented in `indexer.c`, implements an indexer, and exports the following function:

```c
index_t* indexBuild(char* pageDirectory, FILE* fp);
void indexPage(webpage_t* page, int docID, index_t* index, FILE* fp){
int main(int argc, char* argv[]);
```


### Implementation

We implement this with the help of a hashtable and a counter. The functions used to implement them are static and are present in the index module. 

### Assumptions

The content of the index file follows the format specified below; thus our code (to recreate an index structure by reading a file) need not have extensive error checking.

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
