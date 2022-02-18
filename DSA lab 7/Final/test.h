#include "sort.h"
#include "sys/time.h"
#include "stdlib.h"

#ifndef cmp_struct
#define cmp_struct
struct cmpSort {
    float Insort;
    float Qsort;
};
#endif

// cmpSort compares the running time of both InsertionSort and QuickSort.
// It runs both the algorithms on 2 arrays with the same content.
// Returns an object containing both the running times in us(double).
struct cmpSort testRun(struct employee* DataArray, long long N, long long size); 

// Estimate the array size for which InsertionSort and QuickSort take the same size
// Returns the array size as long long integer.
long long EstimateCutoff(struct employee* DataArray, long long N, long long min, long long max);
