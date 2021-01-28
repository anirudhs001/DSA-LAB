
#include<stdio.h>
#include<stdlib.h>
#include"Stack.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: $ ./exe stackInput.txt\n");
        exit(1); 
    }
    // Create a filepointer and open the file read as command line argument.
    FILE * fileptr = fopen(argv[1], "r");
    // Declare a pointer to a linked list (head) and allocate memory to it.
    struct linkedList * Stackhead = (struct linkedList *) malloc(sizeof(struct linkedList));
    // In a loop read the file and insert elements into the linkedList.
    for (int temp; fscanf(fileptr, "%d", &temp) != EOF;){// read the next element and store into the temp variable.
        // insert temp into the linked list.
        push(Stackhead,temp);
    }// close the file pointer
    fclose(fileptr);

    printStack(Stackhead);

    // test pop a couple of times
    printf("pop once\n");
    pop(Stackhead);
    printStack(Stackhead);

    printf("pop twice\n");
    pop(Stackhead);
    pop(Stackhead);
    printStack(Stackhead);
    
    printf("pop 7 times\n");
    pop(Stackhead);
    pop(Stackhead);
    pop(Stackhead);
    pop(Stackhead);
    pop(Stackhead);
    pop(Stackhead);
    pop(Stackhead);
    printStack(Stackhead);

}

