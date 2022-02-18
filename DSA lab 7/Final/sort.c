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