#include<stdio.h>
#include"stdlib.h" 

//Qnode is a node in the Queue ADT
// elem is the integer value stored at the node
// next points to the next node in the Queue. 
// next points to NULL for the last element in the Queue.
struct Qnode {
    int elem;
    struct Qnode* next;
};

// Queue abstract data Type. 
// front is a pointer to the first node of the Queue.
// rear is a pointer to the last node of the Queue.
struct Queue {
    struct Qnode *front, *rear;
};

// newQ creates a new Queue.
// returns the pointer to the newly created Queue.
struct Queue* newQ();

// isEmptyQ returns 0 if length of q is 0.
// non-zero value otherwise.
int isEmptyQ(struct Queue*);

// delQ deletes a element from the front of the Queue.
// returns the pointer to modified Queue
struct Queue* delQ(struct Queue*);

// front returns the element in the first element in the Queue.
int front(struct Queue*);

// addQ adds a new element to the back of the Queue.
// returns the pointer to the modified Queue.
struct Queue* addQ(struct Queue*, int elem);

// lengthQ return the length of the Queue.
int lengthQ(struct Queue* q);

void printQ(struct Queue* q);