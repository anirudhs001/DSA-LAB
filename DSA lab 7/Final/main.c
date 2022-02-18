
#include "sort.h"
#include "test.h"
#include <stdlib.h>
#include "sys/time.h"

int main(int argc, char const *argv[])
{
    /* code */
    // array for employ data
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

