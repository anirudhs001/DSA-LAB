/* Sample1.c */
#include <stdio.h>
int main()
{
    int num;
    FILE *fptr;
    fptr = fopen("program.txt","w");if(fptr == NULL){printf("Error!");
        exit(1);
    }
    fprintf("Enter num: ");
    scanf("%d",&num);
    fprintf(fptr,"%d",num);
    fclose(fptr);
    return 0;
}
