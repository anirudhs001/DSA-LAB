
#include <stdio.h>
#include <stdlib.h>

struct card
{
    long long cardNum;
    char bankCode[5];
    struct
    {
        int m;
        int y;
    } expDate;
    char firstName[10];
    char lastName[10];
};

struct card *insertInOrder(struct card *cardArr, int *n, int *currSize, struct card card);
struct card *insert(struct card *cardArr, int *n, int *currSize, struct card card);

struct card *IterativeInsertionSort(struct card *cardArr, int *n, int *currSize);
struct card *InsertionSort(struct card *cardArr, int *n, int *currSize, int endIndex, int* addrMain);