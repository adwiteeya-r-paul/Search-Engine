## Adwiteeya Paul (arp), May 14 2025

# Implementation Spec

# Data structures

We use an `index` module that essentially implements a hashtable with a set of counters. Thus, we need to use all three modules (hashtable, set and counters) to build index.

# Control flow
The indexer is implemented in one file indexer.c, with three functions.

 main
 indexBuild
 indexPage

 It also depends on the module index and the module word, which are in the common directory. Functions in pagedir.c are also helpful. 



# Function prototypes

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in index.c and is not repeated here.

```c
index_t* indexBuild(char* pageDirectory, FILE* fp);
void indexPage(webpage_t* page, int docID, index_t* index, FILE* fp);
int main(int argc, char* argv[])
```c 

For index, word and pagedir module, check the README.md of common. 



# Error handling and recovery
All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the mem_assert functions, which result in a message printed to stderr and a non-zero exit status. We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the mem_assert functions), e.g., if a function receives bad parameters.

That said, certain errors are caught and handled internally.

# Testing plan
Here is an implementation-specific testing plan.

## Unit testing
The indextest.c file tests the index module by reading an index from an old index file and saving it elsewhere.


## Integration/system testing

We write a script testing.sh that invokes the indexer many times. 
We test indexer with various invalid arguments. 2. no arguments 3. one argument 4. three or more arguments 5. invalid pageDirectory (non-existent path) 5. invalid pageDirectory (not a crawler directory) 6. invalid indexFile (non-existent path) 7. invalid indexFile (read-only directory) 7. invalid indexFile (existing, read-only file)
Run indexer on a variety of pageDirectories and use indextest as one means of validating the resulting index.
Run valgrind on both indexer and indextest to ensure no memory leaks or errors.