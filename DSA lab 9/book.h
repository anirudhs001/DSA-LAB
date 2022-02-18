#include "wchar.h"

#ifndef b
#define b
struct Book {
    wchar_t ** words;
    long size;
};
#endif

#define MAXSIZE 50

long Hash(wchar_t* string, long baseNumber, long tableSize);

long Collisions(struct Book book, long baseNumber, long tableSize);

struct Book Parser(char* filePath);
