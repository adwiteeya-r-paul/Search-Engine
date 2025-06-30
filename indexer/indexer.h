/* 
* indexer.h - header file for indexer, Adwiteeya Paul (arp), May 14, 2025
* The indexer module builds an index from a directory of web pages.
* It includes functions to build the index, index a page, and save the index to a file.
* It uses a hashtable to store the index and a counters structure to count the occurrences of each word in each page.
* It also includes a main function to test the module.
 */




#ifndef __INDEXER_H
#define __INDEXER_H


//header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/webpage.h"
#include "../common/index.h"


/**************** global functions ****************/

/**************** indexBuild() ****************/
/* 
 * indexBuild: builds the index from the web pages in the directory
 * It takes a pageDirectory and a file pointer as arguments.
 * It returns a pointer to the index.
 */
index_t* indexBuild(char* pageDirectory, FILE* fp);

/**************** indexPage() ****************/
/* 
 * indexPage: indexes a single page
 * It takes a webpage pointer, a document ID, an index pointer, and a file pointer as arguments.
 * It does not return anything.
 */
void indexPage(webpage_t* page, int docID, index_t* index, FILE* fp);


/**************** main() ****************/
/* 
 * The main function for the indexer program.
 * It takes command line arguments:
 * 1. pageDirectory: the directory containing the web pages to index
 * 2. indexFilename: the file to save the index to
 * It returns 0 on success, or an error code on failure.
 */

int main(int argc, char* argv[]);

#endif // __INDEXER_H
