// contains myalloc and myfree functions
#include<stdio.h>
#include<stdlib.h>

long long HEAP_SPACE = 0;

// myalloc creates space in memory for n bytes,
// and updates the global variable HEAP_SPACE.
// returns the address of the allocated memory 
// returns NULL if could not create. 
void* myalloc(long n);

// myfree frees the memory pointed at by the ptr.
// It also updates the global variable HEAP_SPACE,
// according to the input parameter size: the size
// of the memory chunk ptr points at
void myfree(void* ptr,long size);
