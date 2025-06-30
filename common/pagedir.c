/*
 * pagedir.c     Adwiteeya Paul (arp)     May 7, 2025
 Pagedir functions are used to initalize a file for the crawler and to save the crawled pages.
 */

//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <regex.h>
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"
#include "../libcs50/mem.h"
#include "pagedir.h"


//**************** file-local global variables ****************/
                        /* none */

//**************** local types ****************/
                    /* none */

//**************** global types ****************/
                     /* none */

//**************** global functions ****************/
//that is, visible outside this file
//see pagedir.h for comments    

//**************** local functions ****************/
                    /* none */


//**************** pagedir_init() ****************/
/* see pagedir.h for description */

bool pagedir_init(const char* pageDirectory){
    int length = strlen(pageDirectory)+ strlen("/.crawler") + 1;
    char* pathFile = malloc(length);
    strncpy(pathFile, pageDirectory, length);
    strncat(pathFile, "/.crawler", length - strlen(pathFile) - 1);
    
    FILE *fp = fopen(pathFile, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not create a file of form pageDirectory/.crawler\n");
        return false;
    }
    fclose(fp);
    free(pathFile);
    return true;
}

//**************** pagedir_save() ****************/
/* see pagedir.h for description */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID){

    int length = snprintf(NULL, 0, "%s/%d", pageDirectory, docID);
    char* pathFile2 = malloc(length + 1);
    snprintf(pathFile2, length+1, "%s/%d", pageDirectory, docID);

    
    FILE *fp = fopen(pathFile2, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not create or write a file of pageDirectory/id\n");
    }
    fprintf(fp, "%s\n", webpage_getURL(page));
    fprintf(fp, "%d\n", webpage_getDepth(page));
    fprintf(fp, "%s\n", webpage_getHTML(page));
    free(pathFile2);
    fclose(fp);
}

//**************** pagedir_validate() ****************/
/* see pagedir.h for description */
bool pagedir_validate(const char* pageDirectory){
    int length = strlen(pageDirectory)+ strlen("/.crawler") + 1;
    char* pathFile = malloc(length);
    strncpy(pathFile, pageDirectory, length);
    strncat(pathFile, "/.crawler", length - strlen(pathFile) - 1);
    FILE *fp;
    
    if ((fp = fopen(pathFile, "r")) != NULL) {
        fclose(fp);
        free(pathFile);
        return true;
    }
    fclose(fp);
    free(pathFile);
    fprintf(stderr, "Error: could not open the file of form pageDirectory/.crawler\n");
    return false;
}

//**************** pagedir_validate() ****************/
/* see pagedir.h for description */
webpage_t* pagedir_load(char* pageDirectory, int docID){
    int length = snprintf(NULL, 0, "%s/%d", pageDirectory, docID);
    char* pathFile = malloc(length + 2);
    snprintf(pathFile, length+2, "%s/%d", pageDirectory, docID);


    FILE *fp = fopen(pathFile, "r");

    if (fp == NULL) {
        free(pathFile);
        return NULL;
    }
    
    char* url;
    int depth;
    url = file_readLine(fp);
    char* depthAsStr = file_readLine(fp);
    depth = atoi(depthAsStr);
    free(depthAsStr);
    char* remainder = file_readFile(fp);
    webpage_t* page = webpage_new(url, depth, remainder);

    fclose(fp);
    free(pathFile);
    return page;
}
