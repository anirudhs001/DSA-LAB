
#include "card.h"
#include "sys/time.h"

int main(int argc, char *argv[])
{
    /* code */
    if (argc < 2 || argc > 3)
    {
        printf("Usage: ./program <file_to_read> [N]\n");
        printf("N: [optional] number of records to read.\n");
        printf("file_to_read: file containing records\n");
        printf("If file contains < N records, reads the same file multiple times untill n records are read \n");
        exit(1);
    }
    int N = 0;
    if (argc == 2)
        N = __INT_MAX__;
    else if (argc == 3)
    {
        char *tptr;
        N = strtol(argv[2], &tptr, 10);
        tptr = NULL;
    }
    struct timeval start, stop;

    int curr_size = 100;
    struct card *cardArr = (struct card *)malloc(curr_size * sizeof(struct card));
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
    gettimeofday(&start, NULL);
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
        if (i + 1 >= curr_size)
        {
            curr_size = curr_size * 2 + 10; // same algo as in JAVA string buffer
            cardArr = (struct card *)realloc(cardArr, curr_size * sizeof(struct card));
        }

        sscanf(tempstr, "%*[\"]%16lld,%5[^,],%2d%*[/]%4d,%10[^,],%10[^\"]",
               &temp.cardNum,
               temp.bankCode,
               &temp.expDate.m,
               &temp.expDate.y,
               temp.firstName,
               temp.lastName);

        cardArr[i] = temp;
        // sanity check
        // printf("%lld,%s,%d/%d,%s,%s\n", temp.cardNum, temp.bankCode, temp.expDate.m, temp.expDate.y, temp.firstName, temp.lastName);
    }
    gettimeofday(&stop, NULL);
    printf("Reading done. read %d values. time taken = %fus\n",
           i,
           (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_usec - start.tv_usec));
    return 0;
}
