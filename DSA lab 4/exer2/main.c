#include "lib.h"
#include "time.h"
int main(int argc, char *argv[])
{
    int* arr = NULL;
    srand(time(0));
    for (long i = rand(), size = 0; arr = (int *)myalloc(size), arr != NULL; i = (rand() % (int)(1e11) + 1e11))
    {
        size = sizeof(int) * i;
        printf("successfully created array. first locn: %p, last locn: %p\n", arr, &(arr[i - 1]));
        myfree(arr, size);
    }
    return 0;
}
