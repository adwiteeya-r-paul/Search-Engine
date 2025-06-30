/* 
 * index.c - source file for index, Adwiteeya Paul (arp), May 14 2025
 *
 * A *index* is a set of (word,counter) pairs.   
 * A *word* is a string, and a *counter* is a set of (docID,count) pairs.
 * The index is implemented as a hashtable of counters.
 * The index is used to store the words found in a web page and the number of times they occur in that page.
 * The index is built from a directory of web pages.
 * The index is saved to a file in the format:
 * word docID1 count1 docID2 count2 ...
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <regex.h>
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/counters.h"
#include "../libcs50/hash.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"
#include "../common/word.h"
#include "../common/pagedir.h"
#include "index.h"

/**************** local functions ****************/
/* not visible outside this file */
/* see index.h for comments about exported functions */

static void printhash(void* arg, const char* key, void* item);
static void printcounter(void* arg, const int key, int count);
static void itemdelete(void* item);


/**************** local types ****************/

typedef struct index{
    hashtable_t* ht;         // hashtable
} index_t;


/**************** global functions ****************/
/* that is, visible outside this file */
/* see index.h for comments about exported functions */


/**************** index_new() ****************/
/* see index.h for description */
index_t*
index_new(const int num_slots){
    index_t* it = malloc(sizeof(index_t));
    it->ht = hashtable_new(num_slots);
    return it;
}

/**************** index_insert() ****************/
/* see index.h for description */

bool index_insert(index_t* it, const char* key, void* item){
    return hashtable_insert(it->ht, key, item);
}

/**************** index_find() ****************/
/* see index.h for description */

void* index_find(index_t* it, const char* key){
    return hashtable_find(it->ht, key);
}


/**************** index_save() ****************/
/*see index.h for description*/

void index_save(index_t* it, FILE* fp){
    hashtable_iterate(it->ht, fp, printhash);
}


void index_iterate(index_t* it, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item)){
    hashtable_iterate(it->ht, arg, itemfunc);
}


/**************** index_delete() ****************/
/* see index.h for description */

void index_delete(index_t* it){
    hashtable_delete(it->ht, itemdelete); // delete the hashtable
    free(it); // delete the index
}

//static function to print the hashtable
static void printhash(void* arg, const char* key, void* item)
 { 
   if (arg != NULL|| key!= NULL) {
     fprintf(arg, "%s", key);
     counters_iterate(item, arg, printcounter);
     fprintf(arg, "\n");
    }
}

//static function to print the counter
static void printcounter(void* arg, const int key, int count)
{

    if (arg != NULL) {
        fprintf(arg, " %d %d", key, count);
    }

}

//**************** index_read() ****************/
/* see index.h for description */
index_t* index_read(FILE* fp, index_t* index)
{

    while(!feof(fp)){ //check if the end of the line is reached
        char* word = file_readWord(fp); // read the word from the file
        if (index_find(index, word) == NULL){ //check if word is not in the index
            counters_t* wordcounter = counters_new(); //create new counters
            index_insert(index, word, wordcounter); //insert the word in the index
        }
        int docID ; //initialize docID
        int count; //initialize count
        while (fscanf(fp, "%d %d", &docID, &count) == 2){ //check if the end of the line is reached
            counters_set(index_find(index, word), docID, count); //insert the word in the index
        }
        free(word); //free the word
    }
    return index;
}

//static function to delete the item in the hashtable
static void itemdelete(void* item)
 {  
    if (item != NULL){
        counters_t* counter = item;
        counters_delete(counter); // delete the counter 
    } 
}




