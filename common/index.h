/* 
 * index.h - header file for index module, Adwiteeya Paul (arp), May 14, 2025
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

 

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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




/**************** global types ****************/
typedef struct index index_t;  // opaque to users of the module

/**************** functions ****************/

/**************** index_new ****************/
/* Create a new (empty) index object.
 *
 * Caller provides:
 *   number of slots to be used for the index(must be > 0).
 * We return:
 *   pointer to the new index; return NULL if error.
 * We guarantee:
 *   index is initialized empty.
 * Caller is responsible for:
 *   later calling index_delete.
 */
index_t*
index_new(const int num_slots);
/**************** index_insert ****************/
/* Insert item, identified by key, into the given index.
 *
 * Caller provides:
 *   valid pointer to index, valid string for key, valid pointer for item.
 * We return:
 *   false if key exists in ht, any parameter is NULL, or error;
 *   true iff new item was inserted.
 * Notes:
 *   The key string is copied for use by the index; that is, the module
 *   is responsible for allocating memory for a copy of the key, and
 *   later deallocating that memory; thus, the caller is free to re-use or 
 *   deallocate its word after this call.  
 */
bool index_insert(index_t* it, const char* key, void* item);
/**************** index_find ****************/
/* Return the counter associated with the given key.
 *
 * Caller provides:
 *   valid pointer to index, valid string for key.
 * We return:
 *   pointer to the item corresponding to the given key, if found;
 *   NULL if index is NULL, key is NULL, or key is not found.
 * Notes:
 *   the index is unchanged by this operation.
 */
void* index_find(index_t* it, const char* key);


/**************** index_save() ****************/
/* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to index, 
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (key,item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, key, item).
 * Notes:
 *   the order in which index items are handled is undefined.
 *   the index and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */
void index_save(index_t* it, FILE* fp);





 /**************** index_iterate ****************/
 /* Iterate over all items in the table; in undefined order.
 *
 * Caller provides:
 *   valid pointer to index, 
 *   arbitrary void*arg pointer,
 *   itemfunc that can handle a single (key,item) pair.
 * We do:
 *   nothing, if ht==NULL or itemfunc==NULL.
 *   otherwise, call the itemfunc once for each item, with (arg, key, item).
 * Notes:
 *   the order in which index items are handled is undefined.
 *   the index and its contents are not changed by this function,
 *   but the itemfunc may change the contents of the item.
 */


 void index_iterate(index_t* it, void* arg,
    void (*itemfunc)(void* arg, const char* key, void* item));





/**************** index_delete ****************/
/* Delete index, calling a delete function on each counter.
 *
 * Caller provides:
 *   valid index pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if index==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the index itself.
 * Notes:
 *   We free the strings that represent word for each item, because 
 *   this module allocated that memory in index_insert.
 */



void index_delete(index_t* it);


/**************** index_read ****************/
/* Read the index from a file.
 *
 * Caller provides:
 *   valid pointer to file.
 * We return:
 *   pointer to the new index; return NULL if error.
 * We guarantee:
 *   index is initialized empty.
 * Caller is responsible for:
 *   later calling index_delete.
 */


index_t* index_read(FILE* fp, index_t* index);

#endif // __INDEX_H
