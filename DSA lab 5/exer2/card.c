
#include "card.h"

struct card *insertInOrder(struct card *cardArr, int *n, int *currSize, struct card c)
{

    if (*n + 1 >= *currSize)
    {
        *currSize = *currSize * 2 + 10;
        cardArr = (struct card *)realloc(cardArr, sizeof(struct card) * *currSize);
    }
    int i = 0;
    for (i = 0; i < *n; i++)
    {
        if (c.cardNum <= cardArr[i].cardNum)
            break;
    }
    for (int j = *n; j > i; j--)
    {
        cardArr[j] = cardArr[j - 1];
    }
    cardArr[i] = c;

    return cardArr;
}

struct card *insert(struct card *cardArr, int *n, int *currSize, struct card c)
{

    if (*n + 1 >= *currSize)
    {
        *currSize = *currSize * 2 + 10;
        cardArr = (struct card *)realloc(cardArr, sizeof(struct card) * *currSize);
    }
    cardArr[*n] = c;
    return cardArr;
}

struct card *IterativeInsertionSort(struct card *cardArr, int *n, int *currSize)
{
    for (int i = 1; i < *n; i++)
    {
        cardArr = insertInOrder(cardArr, n, currSize, cardArr[i]);
        // shift remaining array to left
        for (int j = i + 1; j < *n; j++)
            cardArr[j] = cardArr[j + 1];
    }
    return cardArr;
}
struct card *InsertionSort(struct card* cardArr, int *n, int* currSize, int e, int* addrMain) {

    if (e == 0) {
        int temp;
        printf("Stack size: %ld\n", addrMain - &temp);
        return cardArr;
    }

    cardArr = InsertionSort(cardArr, n, currSize, e - 1, addrMain);
    cardArr = insertInOrder(cardArr, n, currSize, cardArr[e]);
    // shift remaining array to left
    for (int j = e + 1; j < *n; j++)
        cardArr[j] = cardArr[j + 1];

    // sanity check
    return cardArr;
}