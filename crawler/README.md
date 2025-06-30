## Adwiteeya Paul (arp), May 7, 2025

### crawler

A `crawler` crawls a website and retrieves webpages starting with a specified `URL`. It parses the initial `webpage`, extracts any embedded `URL`s and retrieves those pages, and crawls the pages found at those URLs, but limiting itself to some threshold number of hops from the seedURL, and avoiding visiting any given URL more than once. It saves the `pages`, and the `URL` and `depth` for each, in files. When the crawler process is complete, the indexing of the collected documents can begin.



The `crawler` shall:

*execute from a command line with usage syntax `./crawler seedURL pageDirectory maxDepth` where `seedURL` is an 'internal' directory, to be used as the initial URL, `pageDirectory` is the (existing) directory in which to write downloaded webpages, and `maxDepth` is an integer in range [0..10] indicating the maximum crawl depth.


*mark the `pageDirectory` as a 'directory produced by the Crawler' by creating a file named .crawler in that directory.

*crawl all "internal" pages reachable from `seedURL`, following links to a maximum depth of `maxDepth`; where `maxDepth=0` means that `crawler` only explores the page at `seedURL`, and `maxDepth=1` means that `crawler` only explores the page at `seedURL` and those pages to which `seedURL` links, and so forth inductively.


*print nothing to stdout, other than logging its progress; see an example format in the knowledge unit. Write each explored page to the `pageDirectory `with a unique `document ID`, wherein the document id starts at 1 and increments by 1 for each new page the filename is of form `pageDirectory/id`,
the first and third lines of the file are the `URL` and the `depth `respectively and the rest is `html content` respectively. 

It `exits zero` if successful; exit with an `error message to stderr `and `non-zero exit status` if it encounters an unrecoverable error, including out of memory, invalid number of command-line arguments, seedURL is invalid or not internal, maxDepth is invalid or out of range, unable to create a file of form pageDirectory/.crawler, unable to create or write to a file of form pageDirectory/i


.

### Usage

The *crawler* module, defined in `crawler.h` and implemented in `crawler.c`, implements a crawler, and exports the following function:

```c
int main(const int argc, char* argv[])

```


### Implementation

We implement this with the help of a hashtable and a bag. The functions used to implement them are static and are present in the crawler.c. 

### Assumptions

The ```pageDirectory``` does not contain any files whose name is an integer (i.e., 1, 2,) ...

### Files

* `Makefile` - compilation procedure
* `crawler.h` - the interface
* `crawler.c` - the implementation
* `testing.sh` - test script
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make crawler`.

### Testing

The `testing.sh`

To test, simply `make test`.
See `testing.out` for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
