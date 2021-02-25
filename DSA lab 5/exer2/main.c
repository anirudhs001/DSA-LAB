
#include "card.h"
#include "sys/time.h"

int main(int argc, char *argv[])
{
    /* code */
    if (argc != 4)
    {
        printf("Usage: ./program <file_to_read> N debug\n");
        printf("N: number of records to read.\n");
        printf("file_to_read: file containing records\n");
        printf("debug: (bool) 1 if need to print arr. 0 o.w.\n");
        printf("If file contains < N records, reads the same file multiple times untill n records are read \n");
        exit(1);
    }
    int N = 0, debug = 0;
    char *tptr;
    debug = strtol(argv[3], &tptr, 10);
    N = strtol(argv[2], &tptr, 10);
    tptr = NULL;

    struct timeval start, stop;

    int currSize = 100;
    struct card *cardArr = (struct card *)malloc(currSize * sizeof(struct card));
    FILE *file = fopen(argv[1], "r");
    // can't use file = filestart, both will point to same location if anyone is edited
    if (file == NULL)
    {
        printf("File does not exit\n");
        exit(2);
    }
    struct card temp;
    char tempstr[50];
    int i = 0;
    for (i = 0; i < N; i++)
    {
        if (fscanf(file, "%s\n", tempstr) == EOF)
        {
            if (ftell(file) == 0)
            {
                // file is empty
                printf("File is empty\n");
                exit(3);
            }
            fseek(file, 0, SEEK_SET);
        }

        sscanf(tempstr, "%*[\"]%16lld,%5[^,],%2d%*[/]%4d,%10[^,],%10[^\"]",
               &temp.cardNum,
               temp.bankCode,
               &temp.expDate.m,
               &temp.expDate.y,
               temp.firstName,
               temp.lastName);

        cardArr[i] = temp;
        cardArr = insert(cardArr, &i, &currSize, temp);
        // cardArr = insertInOrder(cardArr, &i, &currSize, temp);
        // sanity check
        if (debug)
            printf("%lld,%s,%d/%d,%s,%s\n", temp.cardNum, temp.bankCode, temp.expDate.m, temp.expDate.y, temp.firstName, temp.lastName);
    }

    if (debug) {
        printf("Unsorted sequence:\n");
        for (int j = 0; j < i; j++) {
            printf("%lld,%s,%d/%d,%s,%s\n",
            cardArr[j].cardNum,
            cardArr[j].bankCode,
            cardArr[j].expDate.m,
            cardArr[j].expDate.y,
            cardArr[j].firstName,
            cardArr[j].lastName);
        }
    }

    // measure sorting time and stack space
    int t;
    gettimeofday(&start, NULL);
        cardArr = InsertionSort(cardArr, &i, &currSize, i - 1, &t);
    gettimeofday(&stop, NULL);
    printf("Sorting done. sorted %d values. time taken = %fus\n",
           i, (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_usec - start.tv_usec));

    if (debug) {
        printf("Sorted sequence:\n");
        for (int j = 0; j < i; j++) {
            printf("%lld,%s,%d/%d,%s,%s\n",
            cardArr[j].cardNum,
            cardArr[j].bankCode,
            cardArr[j].expDate.m,
            cardArr[j].expDate.y,
            cardArr[j].firstName,
            cardArr[j].lastName);
        }
    }
    return 0;
}
