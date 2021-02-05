#include"muliq.h"


struct MultiQ* createMQ(int num) {
    // initialise array of length num
    struct MultiQ* mq = (struct MultiQ*)malloc(sizeof(struct MultiQ*)) ; 
    mq->Qarr = (struct Queue**)malloc(num * sizeof(struct Queue*));
    mq->num = num;
    for (int i=1; i<=num; i++) {
        (mq -> Qarr)[i - 1] = newQ();
    }
    return mq;
}

struct MultiQ* addMQ(struct MultiQ* mq, struct Task* t) {
    if (t -> priority > mq -> num) {
        printf("Can't add task of priority %d in Multi Queue of size %d\n", t -> priority, mq -> num);
        return NULL;
    }
    int p = t -> priority;
    addQ((mq -> Qarr)[p-1], t -> TaskID);
    return mq;
}

struct Qnode* nextMQ(struct MultiQ* mq) {
    int p_max = -1;
    int i = mq->num;
    for (; i > 0; i--) 
        if (isEmptyQ((mq -> Qarr)[i - 1])) {
            p_max = i;
            break;
        }
    if (p_max == -1) 
        return NULL;
    return (mq->Qarr)[p_max-1] -> front;
}

struct MultiQ* delNextMQ(struct MultiQ* mq) {
    int p_max = -1;
    int i = mq->num;
    for (; i > 0; i--) {

        if (!isEmptyQ((mq -> Qarr)[i - 1])) {
            p_max = i;
            break;
        }
    }
    if (p_max == -1) 
        return mq;
    
    // move front to next node and delete first node of this Queue
    struct Qnode* temp_front = (mq->Qarr)[p_max - 1] -> front;
    (mq->Qarr)[p_max - 1] -> front = temp_front -> next; 
    free(temp_front);

    return mq;
}

int isEmpty(struct MultiQ* mq) {
    if (sizeMQ(mq) != 0) 
        return 1;
    return 0;
}

int sizeMQ(struct MultiQ* mq) {
    int totalLength = 0;
    for(int i = 1; i <= mq->num; i++) 
        totalLength += sizeMQbyPriority(mq, i);
    return totalLength;
}

int sizeMQbyPriority(struct MultiQ* mq, int priority) {
    return lengthQ(mq->Qarr[priority - 1]);
}

struct Queue* getQueueFromMQ(struct MultiQ* mq, int priority) {
    return mq->Qarr[priority - 1];
}

// Print the entire MultiQ structure
void printMQ(struct MultiQ* mq) {
    printf("Printing entire Multi Queue\n");
    for (int i=1; i <= mq->num; i++) {
        struct Qnode* temp = (mq->Qarr[i - 1])->front;
        printf("%2dth Array: ", i);
        if (temp == NULL) {
            printf("Empty Queue");
        }
        while(temp != NULL) {
            printf("%3d|", temp->elem);
            temp = temp->next;
        } 
        printf("\n");
    }
}