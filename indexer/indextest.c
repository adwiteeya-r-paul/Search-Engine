/*
 * indextest.c     Adwiteeya Paul (arp)     May 14, 2025
    * This file tests the index module.
    * It includes a main function to test the module.
    * Its command line arguments are:
    * 1. oldindexFilename: the file to read the index from
    * 2. newindexFilename: the file to save the index to
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../common/index.h"
#include "../libcs50/file.h"


//**************** main() ****************/
//see above for comments

#ifdef TESTING

int main(int argc, char* argv[]){

    //Check if nunber of arguments is correct
    FILE* fp = fopen(argv[1], "r");
    index_t* index = index_read(fp); //open the file
    fclose(fp); //close the file

    FILE* fp2 = fopen(argv[2], "w");
    index_save(index, fp2); //save the index
    fclose(fp2);
    index_delete(index); //delete the index
}

#endif //TESTING

