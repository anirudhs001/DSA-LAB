#include "linkedlist.h"
#include "lib.h"

void insertFirst(struct linkedList* ll, int ele) {
    //create a node
    struct node *link = (struct node*) myalloc(sizeof(struct node));
    link->element=ele;
    //point it to old first node
    link->next = ll->first;//point first to new first node
    ll->first = link;
    ll->count++;
}

//display the list
// DEPRECATED LOL XD
// this makes less and less sense, since the linked list stores the count too
// USE printListN!!
void printList(struct linkedList * ll) {
    struct node* ptr = ll->first;
    printf("\n[ ");//start from the beginning
    while(ptr != NULL){
        printf("%d,",ptr->element);
        ptr = ptr->next;
    }
    printf(" ]\n");
}

void printListN(struct linkedList* ll, long n) {
    struct node *ptr = ll->first;
    for (long i=0; i < n; i++) {
        printf("[%d,next=%d]",ptr->element, ptr->next?ptr->next->element:-1);
        ptr = ptr->next;
    }
    printf("\n");
}