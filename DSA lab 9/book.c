#include "book.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


// hash a single word
long Hash(wchar_t* string, long baseNumber, long tableSize) {
    long sum = 0;
    for (int i = 0; string[i] != '\0' && i < MAXSIZE; i++) {
        sum += string[i];
    }
    return ( sum % baseNumber ) % tableSize;
}


// count the number of collisions in array book
long Collisions(struct Book book, long baseNumber, long tableSize) {
    long collisions = 0;
    int* seenHashes = calloc(tableSize, sizeof(int));
    for (long i = 0; i < book.size; i++) {
        long hash = Hash(book.words[i], baseNumber, tableSize);
        // first check if this index exists in seenHashes
        if (seenHashes[hash] == 1)
            collisions++;
        else
            seenHashes[hash] = 1;
    }
    return collisions;
}

// parse through file and save all allowed words
struct Book Parser(char* filePath) {

    struct Book book = {NULL, 0};

    wchar_t word[1000];
    wchar_t** words = (wchar_t**)malloc(100 * sizeof(wchar_t*));
    FILE* fptr = fopen(filePath, "rb");
    if (fptr == NULL)
    {
        printf("File does not exist\n");
        return book;
    } 
    int wordAllowed = 1;
    long i = 0;
    while (fwscanf(fptr, L"%ls", word) != EOF) {

        wordAllowed = 1;
        for (int j = 0; j < wcslen(word); j++) {
            if (!((word[j] >= 'a' && word[j] <= 'z') || (word[j] >= 'A' && word[j] <= 'Z'))) {
                wordAllowed = 0;
                break;
            }
        }
        if ( wordAllowed != 1 ) 
            continue;

        // add word in array 
        if (i >= sizeof(book)/sizeof(wchar_t*)) {
            words = (wchar_t**)realloc(words, sizeof(wchar_t*)*(i+101));
        }
        words[i] = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(word) + 1));
        wcscpy(words[i], word);
        i++;
    }
    fclose(fptr); //done reading. close
    // print size of book
    printf("Number of words in book:%ld\n", i);

    // save booksize
    book.words = words;
    book.size = i;
    return book;
}
