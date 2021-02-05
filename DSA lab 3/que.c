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
    new_node -> next = NULL;
    // initialise if array is empty.
    if (q->front == NULL)
        q->front = new_node;
    else
        q->rear->next = new_node;
    
    // add new node to end of queue.
    ( q -> rear ) = new_node;
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

void printQ(struct Queue* q) {
    printf("Queue: ");
    struct Qnode* temp = q->front;
    while(temp != NULL) {
        printf("%3d|", temp->elem);
        temp = temp->next;
    }
    printf("\n");
    if (q->front==NULL)
        printf("front:%p, rear:%p\n", q->front, q->rear);
    else 
        printf("front:%d, rear:%d\n", q->front->elem, q->front->elem);
}