#include "linkedlist.h"
#include "lib.h"

void insertFirst(struct linkedList* ll, long ele) {
    //create a node
    struct node *link = (struct node*) myalloc(sizeof(struct node));
    link->element=ele;
    //point it to old first node
    link->next = ll->first;//point first to new first node
    ll->first = link;
    ll->count++;
}

//display the list
void printList(struct linkedList * ll) {
    struct node* ptr = ll->first;
    printf("\n[ ");//start from the beginning
    while(ptr != NULL){
        printf("%d,",ptr->element);
        ptr = ptr->next;
    }
    printf(" ]\n");
}
