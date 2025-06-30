#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "word.h"

/**************** global functions ****************/
/* that is, visible outside this file */
/* see word.c for comments about exported functions */

char* normalizeWord(char* word){
    for (char* c = word; *c != '\0'; c++){
        *c = tolower(*c);
    }
    return word;
}
