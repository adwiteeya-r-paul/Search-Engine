/*word.c - source file for word module  Adwiteeya Paul (arp), May 14 2025
* A word is a string that is used to identify a set of (docID,count) pairs.
* This module provides functions to normalize a word by converting it to lowercase.
*/

#ifndef __WORD_H
#define __WORD_H

//header files
#include <stdio.h>
#include <stdlib.h>

/**************** global functions ****************/
/* that is, visible outside this file */
/* see above for comments about exported functions */
 
char* normalizeWord(char* word);

#endif // __WORD_H
