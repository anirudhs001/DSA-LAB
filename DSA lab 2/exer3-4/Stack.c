
#include "Stack.h"
void push(struct linkedList* head, int ele) {
    insertFirst(head, ele);
}

struct node* pop(struct linkedList* head) {
    if ( head->count > 0 ) 
        return deleteFirst(head);
    printf("Can't pop from Empty Stack!\n");
    return NULL;
}

void printStack(struct linkedList* head) {
    printf("\nStack right now:\n");
    for (struct node* ptr = head->first; ptr != NULL; ptr=ptr->next) {
        printf("|%3d|\n", ptr->element);
        printf("_____\n");
    }
}
    
