#include"lib.h"

long long int HEAP_SPACE = 0;

void* myalloc(int size) {
    void* ptr = NULL;
    ptr = malloc(size);
    if (ptr == NULL) {
        printf("Error while allocating memory!\n");
        return ptr;
    }

    HEAP_SPACE += size;
    return ptr;
}

void myfree(void* ptr, long size) {
    free(ptr);
    HEAP_SPACE -= size;
}