/* 
 * crawler.h - header file for crawler, Adwiteeya Paul (arp), May 7, 2025
 * A crawler is a program that crawls a web page and saves the pages it finds to a specified directory till a specified depth.
 * It uses a bag to keep track of the pages to crawl and a hashtable to keep track of the pages that have already been seen.
 */


#ifndef __CRAWLER_H
#define __CRAWLER_H

//header files
#include <stdio.h>
#include <stdbool.h>

/**************** functions ****************/

/**************** main() ****************/

/* The main function for the crawler program.
 * It takes command line arguments:
 * 1. seedURL: the URL to start crawling from
 * 2. pageDirectory: the directory to save the crawled pages
 * 3. maxDepth: the maximum depth to crawl
 * It returns 0 on success, or an error code on failure.
 */

int main(const int argc, char* argv[]);

#endif
