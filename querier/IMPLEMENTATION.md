## Adwiteeya Paul (arp), May 23 2025

# Implementation Spec

# Data structures

We use a `querier` module that uses the data structure index (essentiallt hashtable with a set of counters) It builds an index from a file created by the indexer. Earlier, we used all three modules (hashtable, set and counters) to build index. Now we use that structure in querier as our look-up table.

# Control flow
The querier is implemented in one file querier.c, with nine functions.

 main
 parse_query
 verify_query
 tokenize_query
 bnf_query
 score_query
 rank_query
 and_query
 or_query

 It also depends on the module index and the module word, which are in the common directory. Functions in pagedir.c are also helpful. 



# Function prototypes

Detailed descriptions of each function's interface is provided as a paragraph comment in querier.h prior to each function's implementation in querier.c and is not repeated here.

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



For `index`, `word` and `pagedir` module, check the README.md of common. 



# Error handling and recovery


All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the mem_assert functions, which result in a message printed to stderr and a non-zero exit status. We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the mem_assert functions), e.g., if a function receives bad parameters.

That said, certain errors are caught and handled internally.

# Testing plan
Here is an implementation-specific testing plan.


## Integration/system testing

We write a script testing.sh that invokes the querier many times. 
We test `querier` with various invalid arguments. 2. no arguments 3. one argument 4. three or more arguments 5. invalid pageDirectory (non-existent path) 5. invalid pageDirectory (not a crawler directory) 6. invalid indexFile (non-existent path) 7. invalid indexFile (read-only directory) 7. invalid indexFile (existing, read-only file)


We run `querier` on one `crawler` directory and one file produced by the `indexer`.
We also run `valgrind` to check for memory leaks. 



