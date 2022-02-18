// ALL THE CODE IN A SINGLE FILE(INCLUDING HEADER FILES)

////////////////////////////////////////////////////////////////////
//                             main.c                             //
////////////////////////////////////////////////////////////////////

#include "sort.h"
#include "test.h"
#include <stdlib.h>
#include "sys/time.h"

int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        printf("Usage: $ ./exe Infile Outfile N debug\n");
        printf("Infile: file to read employee data from\n");
        printf("Outfile: file to save sorted employee data to\n");
        printf("N: number of values to read\n");
        printf("debug(bool: 1/0): print array values to help debugging\n");
        exit(1);
    }
    char *tptr;
    long long N = strtol(argv[3], &tptr, 10); //size of array
    int debug = strtol(argv[4], &tptr, 10);
    tptr = NULL;

    // read from file
    struct employee *dataArray = (struct employee*) malloc(N * sizeof(struct employee));
    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("File does not exist\n");
        exit(2);
    }
    struct employee temp;
    for(long long i = 0; i < N && fscanf(fptr, "%s%*c%d", temp.name, &temp.ID) != EOF; i++) {
        dataArray[i] = temp;
    }
    fclose(fptr); //done reading. close

    // sanity check
    if (debug == 1) {
        for (int i = 0; i < N; i++)
        {
            printf("%s %d\n", dataArray[i].name, dataArray[i].ID);
        }
    }

    long long min = 1;
    long long max = 1e4;
    long long cutoff = EstimateCutoff(dataArray, N, min, max);
    printf("Estimated cutoff = %lld\n", cutoff);
    // sort with cutoff
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    SplSort(dataArray, cutoff, 0, N-1);
    gettimeofday(&stop, NULL);
    float sortTime = ((stop.tv_sec - start.tv_sec) + 1e6 * (stop.tv_usec - start.tv_usec)) / 1e6;
    printf("Done! time taken = %.0f. Saving file...\n", sortTime);

    if (debug == 1) {
        printf("Sorted array:\n");
        for (int i = 0; i < N; i++)
        {
            printf("%s %d\n", dataArray[i].name, dataArray[i].ID);
        }
    }

    // save sorted array
    fptr = fopen(argv[2], "wb");
    if (fptr == NULL) {
        printf("Outfile does not exist. Could not save.\n");
        exit(2);
    }
    for (long long i=0; i < N; i++ ) {
        fprintf(fptr, "%s,%d\n", dataArray[i].name, dataArray[i].ID);
    }
    fclose(fptr);
    printf("File saved. Exiting\n");

    free(dataArray);
    return 0;
}


////////////////////////////////////////////////////////////////////
//                           sort.h/c                             //
////////////////////////////////////////////////////////////////////

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


#include "sort.h"

void QuickSort(struct employee *DataArray, long long S, long long l, long long r)
{
    if ((r - l) + 1 <= S) 
        return;
    while (l < r)
    {
        long long q = PartitionQS(DataArray, l, r);
        if (q < (l + r) / 2)
        {
            QuickSort(DataArray, S, l, q - 1);
            l = q + 1;
        }
        else
        {
            QuickSort(DataArray, S, q + 1, r);
            r = q - 1;
        }
    }
}

long long PartitionQS(struct employee *DataArray, long long l, long long r)
{
    struct employee pivot = DataArray[r];
    long long i = l - 1;
    long long j = r + 1;
    for (;;)
    {
        while (i<r && DataArray[++i].ID <= pivot.ID)
        {
        }
        while (j>l && DataArray[--j].ID >= pivot.ID)
        {
        }
        if (i < j)
        {
            struct employee temp = DataArray[i];
            DataArray[i] = DataArray[j];
            DataArray[j] = temp;
        }
        else
            break;
    }
    //bring pivot to correct position
    DataArray[r] = DataArray[i];
    DataArray[i] = pivot;
    // return pivot location
    return i;
}

void InsertionSort(struct employee *DataArray, long long l, long long r)
{
    for (int i = l + 1; i <= r; i++)
    {
        struct employee temp = DataArray[i];
        int j = i - 1;
        for (; j >= 0 && DataArray[j].ID > temp.ID; j--)
        {
            DataArray[j + 1] = DataArray[j];
        }
        DataArray[j + 1] = temp;
    }
}

void SplSort(struct employee* DataArray, long long S, long long l, long long r) {
    
    QuickSort(DataArray, S, l, r);
    InsertionSort(DataArray, l, r);
}


////////////////////////////////////////////////////////////////////
//                             test.h/c                           //
////////////////////////////////////////////////////////////////////

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

#include "test.h"


struct cmpSort testRun(struct employee *empData, long long N, long long size)
{
    struct timeval start, stop; //struct to time running time

    // both quicksort and insertion sort are inplace.
    // thus need to make copy of array
    // REMEMBER TO FREE THIS
    struct employee *empDataCopy = (struct employee *)malloc(size * sizeof(struct employee));
    for (long long i = 0; i < size; i++)
        empDataCopy[i] = empData[i];

    // INSERTION SORT 
    gettimeofday(&start, NULL);
    InsertionSort(empDataCopy, 0, size - 1);
    gettimeofday(&stop, NULL);
    float timeInsertionSort = ((stop.tv_sec - start.tv_sec) + 1e6 * (stop.tv_usec - start.tv_usec)) / 1e6;

    // take array back to original state
    for (long long i = 0; i < size; i++)
        empDataCopy[i] = empData[i];
    // QUICK SORT
    gettimeofday(&start, NULL);
    QuickSort(empDataCopy, 0, 0, size - 1);
    gettimeofday(&stop, NULL);
    free(empDataCopy); // FREED HERE
    float timeQuickSort = ((stop.tv_sec - start.tv_sec) + 1e6 * (stop.tv_usec - start.tv_usec)) / 1e6;

    struct cmpSort cmp = {timeInsertionSort, timeQuickSort};
    return cmp; 
}

long long EstimateCutoff(struct employee *empData, long long N, long long min, long long max) {

    if (N < max || min > max) // wrong/unusable values
    {
        printf("Incorrect Array size!\n");
        return 0;
    }
    // Time Insertionsort and Quicksort
    struct cmpSort time1 = testRun(empData,N, min);
    struct cmpSort time2 = testRun(empData,N, max);

    // sanity check
    // printf("run with n = %lld, time_insertionsort = %.0f, time_quicksort = %.0f\n",
        //    min, time1.Insort, time1.Qsort);
    // printf("run with n = %lld, time_insertionsort = %.0f, time_quicksort = %.0f\n",
        //    max, time2.Insort, time2.Qsort);

    struct cmpSort time;
    long long mid = (max + min) / 2;
    do
    {
        time = testRun(empData, N, mid);
        if (time.Insort > time.Qsort)
        { //insertion sort took longer
            max = mid;
        }
        else if (time.Insort < time.Qsort)
        { // quick sort took longer
            min = mid;
        }
        mid = (min + max) / 2;
    } while (time.Insort - time.Qsort > 1. || time.Insort - time.Qsort < -1.);
    // within 1 ms

    return mid;
}
