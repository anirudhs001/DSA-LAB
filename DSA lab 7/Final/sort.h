#include "stdlib.h"
#include<stdio.h>

#ifndef emp_struct
#define emp_struct
struct employee{
    char name[11];
    int ID; 
} ;
#endif

// QuickSort sorts the segment of array DataArray between the
// indices l to r (both inclusive). 
// S+1 gives the smallest size segment that will be sorted
void QuickSort(struct employee* DataArray, long long S, long long l, long long r);

// PartitionQS partitions the array(required by QuickSort)
long long PartitionQS(struct employee *DataArray, long long l, long long r);

// InsertionSort sorts the segment of array DataArray between the
// indices l to r (both inclusive) 
void InsertionSort(struct employee* DataArray, long long l, long long r);


// SplSort first calls QuickSort and then Insertion Sort(for the entire list)
// on the same array
void SplSort(struct employee* DataArray, long long S, long long l, long long r);