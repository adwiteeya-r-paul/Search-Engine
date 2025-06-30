/* 
 * querier.c - source file for querier module,  Adwiteeya Paul (arp), May 24 2025
 * A querier is a program that takes a query from the user and returns the documents that match the query.
 * The querier takes the following arguments:  directory of web pages and an index file.
 * The querier is implemented as a set of functions that parse the query, score the documents, and rank the results from greater to smaller.
 */



/* see index.h for comments about exported functions */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <regex.h>
#include <ctype.h>
#include "querier.h"
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
int currmax = 0; //current maximum score


/**************** local functions ****************/
/* not visible outside this file */

static void and_merge(counters_t* countersA, counters_t* countersB);
static void or_merge(counters_t* countersA, counters_t* counterB);
static void and_merge_helper(void* arg, const int key, const int item);
static void or_merge_helper(void* arg, const int key, const int item);
static void rank_helper(void* arg, const int key, const int item);
static void itemcount(void* arg, const int key, const int count);


/**************** global functions ****************/
/* that is, visible outside this file */
/* see querier.h for comments about exported functions */


/**************** parse_query() ****************/
/* see querier.h for description */


void parse_query(index_t* index, char* pageDirectory){


    char* line; //allocate memory for the line
    printf("Query? \n");
    printf("Query: "); //pronpt the user for a query


    line = file_readLine(stdin); //read the line from stdin
        mem_assert(line, "invalid query"); // check if the line is valid //out of memory error
        int inputlength = strlen(line); //get the length of the line
        printf("Length: %d\n", inputlength); //print the length of the line
        verify_query(line, inputlength); //verify if bad characters are present

        int maxwords = ((inputlength + 1)/2); //maximum number of words possible
        char* words[maxwords]; //array of words

        int nwords = tokenize_query(line, words, inputlength); //tokenize the line
        if (nwords == -1){ //if no words found //defensive programming
            fprintf(stderr, "Error: no words found\n");
        }
        free(line); //free the line
        bnf_query(words, nwords); //parse the line
        score_query(words, nwords, pageDirectory, index); //score the query


        for (int i = 0; i <= nwords; i++){
            free(words[i]); //free the words
        }


}


/**************** verify_query() ****************/
/* see querier.h for description */


void verify_query(char* line, int length){
    int i;
    
    for (i = 0; i < length; i++){ 
        if((isspace((&line[i])[0]) == 0) && (isalpha((&line[i])[0]) == 0)){ //check if not letter or space
            fprintf(stderr, "Error: bad character %c in query\n", (&line[i])[0]); //print the error
            //print the query
        }
    }
}


/**************** tokenize_query() ****************/
/* see querier.h for description */


int tokenize_query(char* line, char* words[], int inputlength){

    char *start, *end;
    start = line; //start pointer
    end = line; //end pointer

    int inword = 0; //boolean to check if in word
    int nword = -1; //word count
    int i;


    for (i = 0; i < inputlength; i++){


        if (((isspace((&line[i])[0]) == 0) && (inword == 0))){ //if a letter and not yet part of a word
    
            inword = 1; //currently in word
            start = &line[i]; //set start pointer to current character
            printf("Start: %s\n", start);
            nword++;
            continue;
        }
    


        if((isspace((&line[i])[0]) == 0) && (inword == 1)){ //if a letter is part of a word
            if ((i == inputlength - 1)){ //if space found while a word was being built
            inword = 0;
            end = &line[i];
            inword = 0; //no longer in word

            char* word = malloc(end - start + 1);
            strncpy(word, start, end - start+1); //copy the word from the line
            word[end - start + 1] = '\0'; //add null terminator


            normalizeWord(word); //normalize the word
            words[nword] = word; //add the word to the array

            printf("Word: %s\n", words[nword]); //print the word
            continue;
            }
        }




        
        if ((isspace((&line[i])[0]) != 0) && (inword == 1)){ //if space found while a word was being built
            end = &line[i-1];
            inword = 0; //no longer in word

            char* word = malloc(end - start +1);
            strncpy(word, start, end - start+1); //copy the word from the line
            word[end - start + 1] = '\0'; //add null terminator


            normalizeWord(word); //normalize the word
            words[nword] = word; //add the word to the array

            printf("Word: %s\n", words[nword]); //print the word
            continue;
        }


        else{ //space followed by space
            continue;
        }          
    }


    free(start); //free the start pointer
    free(end); //free the end pointer

    return nword; //return the number of words

}

/**************** bnf_query() ****************/
/* see querier.h for description */


void bnf_query(char* words[], int nwords){
    char* str1= "and"; //and or
    char* str2 = "or"; //or or

    printf("Words: %s\n", words[0]); //print the first word


    if (((strcmp(words[0],str1)) == 0) || ((strcmp(words[0],str2)) == 0)){ //if begins with 'and' or 'or'
        fprintf(stderr, "%s cannot be the first word\n", words[0]);
    }
    
        for (int i = 0; i < nwords; i++){
            if (((strcmp(words[i],str1)) == 0) || ((strcmp(words[i],str2)) == 0)){ //if 'and' or 'or' is found subsquently
                if (((strcmp(words[i+1],str1)) == 0) || ((strcmp(words[i+1],str2)) == 0)){
                fprintf(stderr, "%s and %s cannot be adjacent\n", words[i], words[i+1]);
                }
            }
        }
    


    if ((strcmp(words[nwords],str1) == 0) || (strcmp(words[nwords], str2) == 0)){ //if ends with 'and' or 'or'
        fprintf(stderr, "%s cannot be the last word\n", words[nwords]);
        }

    }







/**************** score_query() ****************/
/* see querier.h for description */

void score_query(char* words[], int nwords, char* pageDirectory, index_t* index){
    char* str1= "and"; //and or
    char* str2 = "or"; //or or


    counters_t* scores = counters_new(); //create a new counters set 


    //for loop for 'and' queries
    for (int i = 0; i <= nwords; i++){
        if (((strcmp(words[i],str1)) == 0) || ((strcmp(words[i],str2)) == 0)){ //if 'and' or 'or' is found
           continue; //skip
        }


        if ((strcmp(words[i+1],str1)) == 0){        //if next word is 'and'
            scores = and_query(index, words[i], words[i+2]); //call and_query on words before and after 'and'
            continue;

        }


        if (((strcmp(words[i+1],str1)) != 0) || ((strcmp(words[i+1],str2)) != 0)){ //if next word is not 'and' or 'or'
            scores = and_query(index, words[i], words[i+1]); //call and_query on word and next word
            continue;

        }

        if (nwords == 1){ //if only one word is present
            scores = index_find(index, words[i]); //find the word in the index
            continue;
        }

    }

    //for loop for 'or' queries
     for (int i = 0; i <= nwords; i++){
        if ((strcmp(words[i+1],str2)) == 0){  //if next word is 'or'
            scores = or_query(index, words[i], words[i+2]); //call or_query on word and next word
            continue;
        }
    }




    int totaldocs = 0; //total number of documents
    counters_iterate(scores, &totaldocs, itemcount); //count the number of documents
    printf("Matches %d documents\n", totaldocs);

    rank_query(scores, pageDirectory); //rank the scores

    counters_delete(scores); //free the scores

}
    


/**************** rank_query() ****************/
/* see querier.h for description */

void rank_query(counters_t* counter, char* pageDirectory){
    counters_iterate(counter, pageDirectory, rank_helper); //iterate through the counters
}


/**************** and_query() ****************/
/* see querier.h for description */


counters_t* and_query(index_t* index, char* word1, char* word2){
    and_merge(index_find(index, word1), index_find(index, word2));
    return index_find(index, word1); //return the counters 
}


/**************** or_query() ****************/
/* see querier.h for description */

counters_t* or_query(index_t* index, char* word1, char* word2){
    or_merge(index_find(index, word1), index_find(index, word2));
    return index_find(index, word1); //return the counters
}



//static function to merge two counters when 'and' is used
static void and_merge(counters_t* countersA, counters_t* countersB)
{
  counters_iterate(countersB, countersA, and_merge_helper);
}

//static function to merge two counters when'or' is used
static void or_merge(counters_t* countersA, counters_t* countersB)
{
  counters_iterate(countersB, countersA, or_merge_helper);
}

//static helper function for and_merge
static void and_merge_helper(void* arg, const int key, const int item)
{
  counters_t* countersA = arg;
  int itemB = item;
  
  if ((counters_get(countersA, key)) != 0){}
  // find the same key in countersA
  int itemA = counters_get(countersA, key);
    itemA += itemB;
  }


//static helper function for or_merge
static void or_merge_helper(void* arg, const int key, const int item)
{
  counters_t* countersA = arg;
  int itemB = item;
  
  // find the same key in countersA
  
  if ((counters_get(countersA, key)) == 0){
    // not found: insert it
    counters_set(countersA, key, itemB);
    printf("\t%d added\n", key);
  } else {
    int itemA = counters_get(countersA, key);
    // add to the existing value
    itemA += itemB;
    printf("\t%d exists\n", key);
  }
}

//static helper function for rank_query
static void rank_helper(void* arg, const int key, const int item){


    char* pageDirectory = arg;

    //find the max score
    if (item > currmax){
        webpage_t* page = pagedir_load(pageDirectory, key); //load the page
        char* url = webpage_getURL(page); //get the url
        printf("Score  %d doc %s\n", item, url);
        webpage_delete(page); //delete the page
        currmax = item;
    }


}




//static helper function to count the number of items in the counters
static void itemcount(void* arg, const int key, const int count)
 {
   int* nitems = arg;

   if (nitems != NULL){
    (*nitems)++;
   }
 }




/**************** main() ****************/
/* see querier.h for description */

int main(int argc, char*argv[]){
    //Check if the correct number of arguments are passed
    if (argc != 3) {
        fprintf(stderr, "Usage: %s pageDirectory indexFilename\n", argv[0]);
        return 1;
    }
    //Check if directory is produced by crawler
    if (!pagedir_validate(argv[1])){
        fprintf(stderr, "Not a directory produced by crawler\n");
        return 1;
    }
    //Check if index file is valid
        //Check if index file is valid
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        fprintf(stderr, "Not pathname of a file produced by indexer\n");
        return 1;
    }

    const int lines = file_numLines(fp);
    index_t* nindex = index_new(lines);
    index_t* index = index_read(fp, nindex); //open the file

    fclose(fp); //close the file
    parse_query(index, argv[1]); //parse the query
    index_delete(index);
    index_delete(nindex);
}
