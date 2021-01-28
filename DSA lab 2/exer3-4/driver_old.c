/* driver.c */
#include <stdio.h>
#include "stdlib.h"
#include "linkedlist.h"

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Usage: $ ./exe sampleInput.txt <outputFileName.txt>\n");
        exit(1); 
    }
    // Create a filepointer and open the file read as command line argument.
    FILE * fileptr = fopen(argv[1], "r");
    // Declare a pointer to a linked list (head) and allocate memory to it.
    struct linkedList * head = (struct linkedList *) malloc(sizeof(struct linkedList));
    // In a loop read the file and insert elements into the linkedList.
    for (int temp; fscanf(fileptr, "%d", &temp) != EOF;){// read the next element and store into the temp variable.
        // insert temp into the linked list.
        insertFirst(head,temp);
    }// close the file pointer
    fclose(fileptr);
    // print the linked list.
    printList(head); 
    // delete the first element of the linked list.
    deleteFirst(head);
    // print the linked list again to check if delete was successful.
    printList(head);
    // print the linked list to a new file.
    // 1. open file
    FILE* fout = fopen(argv[2], "w+");
    if (fout == NULL) {
        printf("Error opening output file! exiting now.\n");
        fclose(fout);
        exit(1);
    }
    // 2. write to file
    for (struct node* temp = head -> first; temp != NULL; temp = temp -> next) {
        if (fprintf(fout, "%d\n" ,temp->element) < 0) {
            printf("Error writing to file! exiting now.\n");
            fclose(fout);
            exit(2);
        }
    }
    printf("\nSuccesfully wrote list to file.\n");
    fclose(fout);

    // test search and delete
    printf("1 exists in list:%d\n", search(head, 1));
    printf("9 exists in list:%d\n", search(head, 9));
    
    // delete value 9
    delete(head, 9);
    printf("list after deleting value 9:");
    printList(head);

    printf("list after deleting value 1:");
    delete(head, 1);
    printList(head);

    printf("list after deleting value 32:");
    delete(head, 32);
    printList(head);

    printf("list after deleting value 17:");
    delete(head, 17);
    printList(head);
    return 0;
}
