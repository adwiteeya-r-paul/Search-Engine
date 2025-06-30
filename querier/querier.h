//Adwiteeya Paul (arp), May 23 2025
//querier.h - header file for querier module



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/index.h"
#include "../libcs50/counters.h"


/**************** global functions ****************/



/**************** main()*********************/

// This function is the main entry point for the querier module.
// It takes two strings (for the pageDirectory and the indexFileName) as arguments.
// It returns nothing.


int main(int argc, char* argv[]);

/*****************parse_query() **************/

// This function parses the query and calls the appropriate functions to process it.
// It takes an index pointer and a string (for the pageDirectory) as arguments.
// It returns nothing.
// It prompts the user for a query, verifies it, tokenizes it, parses it, and scores it.
// It also frees the memory allocated for the line and the words.



void parse_query(index_t* index, char* pageDirectory);

//**************** verify_query() ****************/

// This function verifies the query for bad characters.
// It takes a string (for the line) and an integer (for the length) as arguments.
// It returns nothing.
// It checks if the line contains any characters that are not letters or spaces.


void verify_query(char* line, int length);


//**************** tokenize_query() ****************/

// This function tokenizes the query into words.
// It takes a string (for the line), an array of strings (for the words), and an integer (for the input length) as arguments.
// It returns the number of words.
// It uses a start and end pointer to find the words in the line.
// It also normalizes the words and adds them to the array of words.

int tokenize_query(char* line, char* words[], int inputlength);


//**************** bnf_query() ****************/
// This function checks the query for the presence of 'and' and 'or'.
// It takes an array of strings (for the words) and an integer (for the input length) as arguments.
// It returns nothing.
// It checks if 'and' or 'or' is the first word, the last word, or adjacent to another 'and' or 'or'.

void bnf_query(char* words[], int inputlength);

//**************** score_query() ****************/
// This function scores the query and ranks the results.
// It takes an array of strings (for the words), an integer (for the input length), a string (for the pageDirectory), and an index pointer as arguments.
// It returns nothing.

void score_query(char* words[], int inputlength, char* pageDirectory, index_t* index);


//**************** rank query() ****************/
// This function ranks the query results.
// It takes a counters pointer and a string (for the pageDirectory) as arguments.

void rank_query(counters_t* counter, char* Directory);


//**************** and_query() ****************/
// This function performs an 'and' query on the index.
// It takes an index pointer and two strings (for the words) as arguments.
// It returns a counters pointer.
counters_t* and_query(index_t* index, char* word1, char* word2);

//**************** or_query() ****************/
// This function performs an 'or' query on the index.
// It takes an index pointer and two strings (for the words) as arguments.
// It returns a counters pointer.

counters_t* or_query(index_t* index, char* word1, char* word2);
