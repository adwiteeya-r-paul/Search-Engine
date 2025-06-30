## Adwiteeya Paul (arp), May 14, 2025

### common

The `common` library, for now, comprises code for initializing the `pageDirectory` and saving webpages there, validating if a directory is produced by crawler and loading an index.  It also has `index` module that provides with functions that can create the index for webpages. It also has  `word` module that normalizes a word. It assembles code that will eventually be shared by the `crawler`, `indexer`, and `querier`. 
.

### Usage

Common, for now, has `pagedir.h` and `pagedir.c`, with the following functions:

```c
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
webpage_t* pagedir_load(char* pageDirectory, int docID);


```

Common also has `index.h` and `index.c` with functions:

```c
typedef struct index index_t;  
index_t*
index_new(const int num_slots);
bool index_insert(index_t* it, const char* key, void* item);
void* index_find(index_t* it, const char* key);
void index_save(index_t* it, FILE* fp);
void index_delete(index_t* it);
index_t* index_read(FILE* fp);

```

and  `word.c` and `word.h` with functions:

```c
char* normalizeWord(char* word);

```

### Implementation

The implementation of pagedir is very simple and relies on a boolean and a void function with simple fopen and fclose operations. For index, it mostly is a wrapper module for hashtable. And for word, there is only one function.

### Assumptions

The assumption currently is the same as the assumption under `crawler`:
The ```pageDirectory``` does not contain any files whose name is an integer (i.e., 1, 2,) ...

### Files

* `Makefile` - compilation procedure
* `pagedir.h` - the interface
* `pagedir.c` - the implementation
* `index.h` - the interface
* `index.c` - the implementation
* `word.h` - the interface
* `word.c` - the implementation



### Compilation

To compile, simply `make common.a`.

### Testing

Currently no testing files as it can be tested using crawler.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.

To test with valgrind, `make valgrind`.
