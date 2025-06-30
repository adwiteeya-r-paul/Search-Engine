## Implementation Spec

In this document, the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) are referenced and the focus is on the implementation-specific decisions.
Here we focus on the core subset:

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan

## Data structures 

Crawler uses two data structures: a 'bag' of pages that need to be crawled, and a 'hashtable' of URLs that have been seen during crawl.
Both start empty. The size of the hashtable (slots) is impossible to determine in advance, I use 200.

## Control flow

The Crawler is implemented in one file `crawler.c`, with four functions.

### main

The `main` function simply calls `parseArgs` and `crawl`, then exits zero.

### parseArgs

Given arguments from the command line, extract them into the function parameters; return only if successful.

* for `seedURL`, normalizing the URL and validating it is an internal URL
* for `pageDirectory`, calling `pagedir_init()`
* for `maxDepth`, ensuring it is an integer in specified range
* if any trouble is found, printing an error to stderr and exiting non-zero.

### crawl

Does the main crawling from `seedURL` to `maxDepth` and saves pages in `pageDirectory`:
Pseudocode:

	initialize the hashtable and add the seedURL
	initialize the bag and add a webpage representing the seedURL at depth 0
	while bag is not empty
		pull a webpage from the bag
		fetch the HTML for that webpage
		if fetch was successful,
			save the webpage to pageDirectory
			if the webpage is not at maxDepth,
				pageScan that HTML
		delete that webpage
	delete the hashtable
	delete the bag

### pageScan

This function implements the *pagescanner* mentioned in the design.
Given a `webpage`, the given page is scanned to extract any links (URLs), ignoring non-internal URLs; for any URL not already seen before (i.e., not in the hashtable), add the URL to both the hashtable `pages_seen` and to the bag `pages_to_crawl`.
Pseudocode:

	while there is another URL in the page
		if that URL is Internal,
			insert the webpage into the hashtable
			if that succeeded,
				create a webpage_t for it
				insert the webpage into the bag
		free the URL

## Other modules

### pagedir

This is a re-usable module that handles the *pagesaver*  mentioned in the design (writing a page to the pageDirectory), and marking it as a Crawler-produced pageDirectory (as required in the spec).

Pseudocode for `pagedir_init`:

	construct the pathname for the .crawler file in that directory
	open the file for writing; on error, return false.
	close the file and return true.


Pseudocode for `pagedir_save`:

	construct the pathname for the page file in pageDirectory
	open that file for writing
	print the URL
	print the depth
	print the contents of the webpage
	close the file

### libcs50

Crawler leverages the modules of libcs50, most notably `bag`, `hashtable`, and `webpage`.
See that directory for module interfaces.
The new `webpage` module represents pages as `webpage_t` objects, to fetch a page from the Internet, and to scan a (fetched) page for URLs; in that regard, it serves as the *pagefetcher* described in the design.
Indeed, `webpage_fetch` enforces the 1-second delay for each fetch, so the crawler need not implement that part of the spec.

## Function prototypes

### crawler

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in `crawler.c` and is not repeated here.

```c
int main(const int argc, char* argv[]);
static void parseArgs(const int argc, char* argv[],
                      char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
```

### pagedir

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `pagedir.h` and is not repeated here.

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
```

## Error handling and recovery

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

Out-of-memory errors are handled by variants of the `mem_assert` functions, which result in a message printed to stderr and a non-zero exit status.
We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the `mem_assert` functions), e.g., if a function receives bad parameters.

That said, certain errors are caught and handled internally: for example, `pagedir_init` returns false if there is any trouble creating the `.crawler` file, allowing the Crawler to decide what to do; the `webpage` module returns false when URLs are not retrievable, and the Crawler does not treat that as a fatal error.

## Testing plan

Here is an implementation-specific testing plan.

### Integration/system testing

I wrote a script `testing.sh` that invokes the crawler several times, with a variety of command-line arguments.
First, a sequence of invocations with erroneous arguments, testing each of the possible mistakes that can be made.
Second, a run with valgrind over a moderate-sized test case (such as `toscrape` at depth 1).
Third, runs over all three CS50 websites (`letters` at depths 0,1,2,10, `toscrape` at depths 0,1,2,3, `wikipedia` at depths 0,1,2).
I run that script with `bash -v testing.sh` so the output of crawler is intermixed with the commands used to invoke the crawler.
I verified correct behavior by studying the output, and by sampling the files created in the respective pageDirectories.

