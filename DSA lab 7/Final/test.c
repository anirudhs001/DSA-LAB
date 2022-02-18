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
