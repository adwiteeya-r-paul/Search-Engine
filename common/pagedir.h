/* 
 * pagedir.h - header file for pagedir.c, Adwiteeya Paul (arp), May 7, 2025
 * pagedir functions are used to initalize a file for the crawler and to save the crawled pages.
 */


#ifndef __PAGEDIR_H
#define __PAGEDIR_H

//header files
#include <stdio.h>
#include <stdlib.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
//**************** functions ****************/


/***************** pagedir_init() ***********/
/*
* A function to initialize a file for the crawler.
* It takes a string (for the pageDirectory) as an argument and creates a file with the name of the string + "/.crawler".
*/

bool pagedir_init(const char* pageDirectory);


/****************** pagedir_save **************/
/*
* A function to save the crawled pages to a specified directory.
* It takes a webpage pointer, a string (for the pageDirectory), and an integer (for the docID) as arguments.
* It creates a file with the name of the string + "/" + docID and saves the crawled page to that file.
* It saves the URL, depth, and HTML of the crawled page to the file.
* It returns nothing.
*/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);


/****************** pagedir_validate() **************/
/* This function checks if the pageDirectory is valid.
* It takes a string (for the pageDirectory) as an argument and checks if the file of form pageDirectory/.crawler exists.
* It returns true if the file exists and false if it does not.
* It also prints an error message if the file does not exist.
* It returns true if the file exists and false if it does not.
*
*/
bool pagedir_validate(const char* pageDirectory);


/****************** pagedir_load() **************/
/* This function loads a webpage from the pageDirectory.
* It takes a string (for the pageDirectory) and an integer (for the docID) as arguments.
* It creates a file with the name of the string + "/" + docID and loads the webpage from that file.
* It returns a webpage pointer.
* It returns NULL if the file does not exist.
* It also prints an error message if the file does not exist.
* It returns a webpage pointer.
*/

webpage_t* pagedir_load(char* pageDirectory, int docID);

#endif
