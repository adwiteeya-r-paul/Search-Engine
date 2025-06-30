/*
 * crawler.c     Adwiteeya Paul (arp)     May 7, 2025
 *
 * This file works on the crawler.
 * It crawls a web page and saves the pages it finds to a specified directory till a specified depth.
 * It uses a bag to keep track of the pages to crawl and a hashtable to keep track of the pages that have already been seen.
 * Its command line arguments are:
 *  1. seedURL: the URL to start crawling from
 *  2. pageDirectory: the directory to save the crawled pages
 *  3. maxDepth: the maximum depth to crawl
 * It includes functions:
 * 1. parseArgs: parses the command line arguments
 * 2. crawl: crawls the web page and saves the pages it finds
 * 3. pageScan: scans the web page for URLs and adds them to the bag of pages to crawl
 * 4. main: the main function 
 */

//header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "crawler.h"
#include "../libcs50/bag.h"
#include "../libcs50/set.h"
#include "../libcs50/hash.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"

/**************** file-local global variables ****************/
                        /* none */

/**************** local types ****************/
                        /* none */

/**************** global types ****************/
                        /* none */

/**************** global functions ****************/
/*that is, visible outside this file */
/*see crawler.h for comments*/

/**************** local functions ****************/
/*not visible outside this file */
static void parseArgs(const int argc, char* argv[],char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

//parsing the command line arguments
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth){
    
    //parsing the seedURL
    char* url = *seedURL; 
    char* nurl = normalizeURL(url); // normalize the URL
    mem_assert(nurl, "invalid seedurl"); // check if the URL is valid
    if (isInternalURL(nurl) == false){ // check if the URL is internal
            fprintf(stderr, "Error: %s is not an internal URL\n", url);
            exit(1);
    }
    free(nurl); // free the normalized URL

    //parsing the pageDirectory
    pagedir_init(*pageDirectory); // initialize the page directory
    mem_assert(*pageDirectory, "Invalid pageDirectory"); // check if the page directory is valid


    //parsing the maxDepth
    if (*maxDepth < 0 || *maxDepth > 10){ // check if the max depth is valid
        fprintf(stderr, "maxDepth must be a non-negative integer from 0 to 10\n");
        exit(1);
    }
}

//crawling the web page and saving them
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth){
    
    //copying the seed URL to a new variable to avoid modifying the original seed URL
    int len = strlen(seedURL) + 1; // length of the seed URL and +1 for the null terminator
    char* url = malloc(len); // allocate memory for the URL
    mem_assert(url, "memory allocation error"); // check if the memory allocation was successful
    strncpy(url, seedURL, len);  // copy the seed URL to the allocated memory

    //normalizing the seed URL
    char* nurl = normalizeURL(url);  
    mem_assert(nurl, "invalid seedurl"); // check if the URL is valid

    //free the unnormalized URL variable
    free(url); 


    //initialize the hashtable and add the seedURL to it; check if the hashtable was created successfully (defensive programming)
    hashtable_t* pagesSeen = hashtable_new(200);
    hashtable_insert(pagesSeen, nurl, "");
    mem_assert(pagesSeen, "Error: could not create hashtable\n"); 

    //initialize the bag and add the seedURL to it; check if the bag was created successfully (defensive programming)
    bag_t* pagesToCrawl = bag_new();
    mem_assert(pagesToCrawl, "Error: could not create bag\n");

    //create a new webpage with the normalized url and add it to the bag; check if the bag was created successfully (defensive programming)
    webpage_t* page = webpage_new(nurl, 0, NULL);
    mem_assert(page, "Error: could not create webpage\n"); // check if the webpage was created successfully
    
    //insert the webpage into the bag
    bag_insert(pagesToCrawl, page);

    //initialize docID to 0
    int docID = 0;

    //initialize the webpage pointer
    webpage_t* currpage;

    while ((currpage = bag_extract(pagesToCrawl)) != NULL) { //while there are pages to crawl
        printf("Crawling: %s\n", webpage_getURL(currpage));
        if(webpage_fetch(currpage)){ //fetch the webpage
            docID++; // increment the docID
            printf("%d   Fetched: %s\n", webpage_getDepth(currpage), webpage_getURL(currpage)); 
            pagedir_save(currpage, pageDirectory, docID); //save the webpage to the page directory
            if (webpage_getDepth(currpage) < maxDepth){  //check if the depth is less than maxDepth
                printf("%d   Scanning: %s\n", webpage_getDepth(currpage), webpage_getURL(currpage));
                pageScan(currpage,pagesToCrawl, pagesSeen);  //scan the webpage for URLs
            }     
        }      
        webpage_delete(currpage);   // delete the webpage whether or not it was fetched

    } 
    hashtable_delete(pagesSeen, NULL); // delete the hashtable
    bag_delete(pagesToCrawl,webpage_delete); // delete the bag
}

//scanning the webpage for URLs and adding them to the bag for future crawling
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen){ 
    int pos = 0;
    char* result;
 
    while ((result = webpage_getNextURL(page, &pos)) != NULL) {//while there are URLs to scan
        char* normURL = normalizeURL(result); // normalize the URL
        if (normURL == NULL){ // check if the URL is valid
            fprintf(stderr, "Error: %s is not a valid URL\n", result);
            free(normURL); // free the normalized URL
            continue; // skip to the next URL
        }
        else{ 
            printf("%d   Found: %s\n", webpage_getDepth(page), normURL);
            if (isInternalURL(normURL)){ 
                //internal URL
                if (hashtable_insert(pagesSeen, normURL, "")){    
                    //did not see this URL before   
                    webpage_t* newPage = webpage_new(normURL, webpage_getDepth(page)+1, NULL); // create a new webpage with the normalized URL
                    bag_insert(pagesToCrawl, newPage); // insert the new webpage into the bag
                    printf("%d   Added: %s\n", webpage_getDepth(page), normURL); //printing the depth of the original page and the new URL
                }
                else{  
                    //already seen URL
                    printf("%d   IgnDupl: %s\n", webpage_getDepth(page), normURL); 
                    free(normURL); // free the normalized URL
                    continue; // skip to the next URL
                }
            }
            else{
                //external URL
                printf("%d   IgnExtrn: %s\n", webpage_getDepth(page), normURL); //external URL
                free(normURL); // free the normalized URL
                continue; // skip to the next URL
            }
        }


        // free the found URl 
        free(result);
    }
}

int main(const int argc, char* argv[]){ // main function

    if (argc != 4 || argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){ //check if all command line arguments are provided
        fprintf(stderr, "Usage: seedURL, pageDirectory, maxDepth\n");
        exit(1);
    }     
    int maxdepth = atoi(argv[3]); // convert the max depth to an integer
    parseArgs(argc, argv, &argv[1], &argv[2], &maxdepth); // parse the command line arguments
    crawl(argv[1], argv[2], maxdepth); // crawl the web page and save the pages it finds
    exit(0);  // return 0 to indicate success
}




