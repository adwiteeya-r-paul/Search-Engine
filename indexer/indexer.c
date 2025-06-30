/*
 * index.c     Adwiteeya Paul (arp)     May 14, 2025
 * The indexer module
 * This module builds an index from a directory of web pages.
 * It includes functions to build the index, index a page, and save the index to a file.
 * It uses a hashtable to store the index and a counters structure to count the occurrences of each word in each page.
 * It also includes a main function to test the module.
 * The command line arguments are:
 * 1. pageDirectory: the directory containing the web pages to index
 * 2. indexFilename: the file to save the index to
 * It includes functions:
 * 1. indexBuild: builds the index from the web pages in the directory
 * 2. indexPage: indexes a single page
 * 3. main: the main function to test the module

 */


//header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <regex.h>
#include "indexer.h"
#include "../libcs50/webpage.h"
#include "../common/index.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hash.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/word.h"


/**************** file-local global variables ****************/
                        /* none */

/**************** local types ****************/
                        /* none */

/**************** global types ****************/
                        /* none */

/**************** global functions ****************/
/*see indexer.h for comments*/

/**************** local functions ****************/
/*none*/


/**************** indexBuild() ****************/
//see indexer.h for comments
index_t* indexBuild(char* pageDirectory, FILE* fp){
    index_t* index = index_new(900); //create new index
    int docID = 1;
    webpage_t* page; 
    while((page = pagedir_load(pageDirectory, docID))!= NULL){ //load the page
        indexPage(page, docID, index, fp); //index the page
        webpage_delete(page); //delete the page
        docID++; //increment the docID
    }

    return index;
}


/**************** indexPage() ****************/
//see indexer.h for comments
void indexPage(webpage_t* page, int docID, index_t* index, FILE* fp){
    int pos = 0; //position of the word
    char* word = NULL;
    while ((word = webpage_getNextWord(page, &pos)) != NULL){ //check if word is not NULL
        if (strlen(word) > 2){ //check if word is greater than 2
            normalizeWord(word); //normalize the word
            if (index_find(index, word) == NULL){ //check if word is not in the index
                counters_t* wordcounter = counters_new(); //create new counters
                index_insert(index, word, wordcounter); //insert the word in the index
            }
            counters_add(index_find(index, word), docID) ; //insert the word in the index with +1 count
        }
        free(word); //free the word
    }
}


#ifndef TESTING
/**************** main() ****************/
//see indexer.h for comments
int main(int argc, char* argv[]){
    //Check if nunber of arguments is correct
    if (argc != 3 || argv[1] == NULL || argv[2] == NULL){ //check if all command line arguments are provided
        fprintf(stderr, "Usage: pageDirectory, indexFilename\n");
        exit(1);
    }

    //Check if directory is produced by crawler
    if (pagedir_validate(argv[1]) == false){
        fprintf(stderr, "Not a directory produced by crawler\n");
        exit(1);
    }
      
    //Check if index file is valid
    FILE *fp = fopen(argv[2], "w");
    if (fp == NULL) {
        fprintf(stderr, "Not pathname of a file that can be written into");
        exit(1);
    }

    index_t* index = indexBuild(argv[1], fp); //build the index    
    index_save(index, fp); //save the index
    index_delete(index); //delete the index
    fclose(fp); //close the file
}

#endif //TESTING

    