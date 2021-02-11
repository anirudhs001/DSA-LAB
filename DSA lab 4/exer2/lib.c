#include"lib.h"

void* myalloc(long n) {
    void* ptr = NULL;
    ptr = malloc(n);
    if (ptr != NULL)
        HEAP_SPACE += n;
    return ptr;
}

void myfree(void* ptr, long size) {
    free(ptr);
    HEAP_SPACE -= size;
}