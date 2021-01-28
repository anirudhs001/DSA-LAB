
#include "stdlib.h"
#include "linkedlist.h"

void insertFirst(struct linkedList* head, int ele) {
    //create a node
    struct node *link = (struct node*) malloc(sizeof(struct node));
    /*by this you are creating a node whose address is being stored in the link pointer.*/
    link->element=ele;
    //point it to old first node
    link->next = head->first;//point first to new first node
    head->first = link;
    head->count++;
}

struct node* deleteFirst(struct linkedList *head) {
    struct node* temp = head -> first;
    head->first = temp -> next;
    head -> count--;      
    // return freed memory
    return temp;
}

//display the list
void printList(struct linkedList * head) {
    struct node* ptr = head->first;
    printf("\n[ ");//start from the beginning
    while(ptr != NULL){
        printf("%d,",ptr->element);
        ptr = ptr->next;
    }
    printf(" ]\n");
}

int search(struct linkedList* head, int ele) {
    struct node* ptr = head->first; 
    for(; ptr != NULL; ptr = ptr -> next) {
        if (ptr -> element == ele) {
            return 1;
        }
    }
    return 0;
}

struct node * delete (struct linkedList * head, int ele) {
    if (head -> count != 0) {
        struct node* ptr_prev = head->first; 
        struct node* ptr = ptr_prev->next;

        if ((head->first)->element == ele) {
            head->first = (head->first)->next;
            return ptr_prev;
        }
        // this stratagy can't check the first node. the if condition above does.
        for(; ptr != NULL; ptr = ptr -> next, ptr_prev = ptr_prev->next) {
            if (ptr -> element == ele) {
                ptr_prev -> next = ptr -> next;
                return ptr;
            }
        }
    }
    printf("Value not found in list\n");
    return NULL;
}
