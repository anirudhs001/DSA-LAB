// Multi Queue implementation using Queues from que.h

#include"que.h"

// MutliQ Abstract Datatype 
struct MultiQ {
    struct Queue* Qarr;
    int num;
};

// Task 
// TaskID is unique value for each task
// priority is the priority value for each task
struct Task {
    int TaskID;
    int priority;
};

// MultiQ creates and allocates space in memory to store "num" Queues.
// All the Queues in MultiQ are initialised to null.
// returns the pointer to the newly created MultiQueue.
struct MultiQ* createMQ(int num);

// addMQ adds the Task t in a Queue of matching priority
// if no Queue of matching priority is found in the MultiQ, it initializes an empty 
// Queue with the Task t.
// returns a pointer to the modified Multi Queue.
struct MultiQ* addMQ(struct MultiQ* mq, Task* t);

// nextMQ finds the task in the front from the Queue with the highest priority.
// returns the pointer to this task.
struct Task* nextMQ(struct MultiQ* mq);

// delNextMQ deletes the task in front from the Queue with the highest priority.
// returns the address to the modified MultiQ
struct MultiQ* delNextMQ(struct MultiQ* mq);

// isEmpty checks size of MultiQ.
// returns 1 if all the queues in the Multi are empty, 0 o.w. .
int isEmpty(struct MultiQ* mq);

// sizeMQ returns total number of items in the MultiQ
int sizeMQ(struct MultiQ* mq);

// sizeMQbyPriority returns the number of items in Queue with priority p
int sizeMQbyPriority(struct MultiQ* mq, int priority);

// getQueueFromMQ returns pointer to Queue with priority p
struct Queue* getQueueFromMQ(struct MultiQ* mq, int priority);