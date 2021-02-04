// Implementation of Queue ADT (in que.h) using LinkedList
#include"que.h"

// newQ creates a new Queue.
// returns the pointer to the newly created Queue.
struct Queue* newQ() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q -> front = NULL;
    q -> rear = NULL;
    return q;
}

// isEmptyQ returns 1 if length of q is 0.
// zero otherwise.
int isEmptyQ(struct Queue* q) {
    if (lengthQ(q) == 0)
        return 1;
    return 0;
}

// delQ deletes a element from the front of the Queue.
// returns the pointer to modified Queue
struct Queue* delQ(struct Queue* q) {
    struct Qnode* temp_front = q -> front;
    q -> front = (q -> front) -> next;
    // deallocate memory
    free(temp_front);
    return q;
}

// front returns the value of the first element in the Queue.
int front(struct Queue* q) {
    return q -> front -> elem;
}

// addQ adds a new element to the back of the Queue.
// returns the pointer to the modified Queue.
struct Queue* addQ(struct Queue* q, int elem) {
    struct Qnode* new_node = (struct Qnode*)malloc(sizeof(struct Qnode));
    new_node -> elem = elem;
    ( q -> rear ) -> next = new_node;
    q -> rear = new_node;
    new_node -> next = NULL;
    return q;
}
// lengthQ return the length of the Queue.
int lengthQ(struct Queue* q) {
    struct Qnode* temp = q -> front;
    int len = 0;
    while (temp != NULL) {
        len++;
        temp = temp -> next;
    }
    return len;
}