#include"muliq.h"

#define NUM 10

struct MultiQ* loadData(struct MultiQ*, FILE*);
struct MultiQ* testDel(struct MultiQ* mq, int num);

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        printf("Usage: $ ./exe <Input.txt>\n");
        exit(1); 
    }
    // Create a filepointer and open the file read as command line argument.
    // test Queue
    struct Queue* q = newQ();
    printQ(q);
    q = addQ(q, 10);
    printQ(q);
    
    //test Multi Q
    struct MultiQ* mq = createMQ(NUM);
    printMQ(mq);
    // add temp element
    struct Task t = (struct Task){5, 5};
    printf("Adding task with id=%d and priority=%d\n",t.TaskID, t.priority );
    mq = addMQ(mq, &t);
    printMQ(mq);
    // delete temp element
    printf("Deleting latest task\n");
    mq = delNextMQ(mq);
    printf("\n\n");

    // EXERCISE 3.a
    // Create a filepointer and open the file read as command line argument.
    printf("Reading file...\n");
    FILE* fileptr = fopen(argv[1], "r");
    mq = loadData(mq, fileptr);
    fclose(fileptr);
    printMQ(mq);
    printf("\n\n");
    
    // call testDel
    int num = 50;
    printf("Perform delNextMQ %d times\n", num);
    mq = testDel(mq, 10);
    printMQ(mq);
    return 0;

}

struct MultiQ* loadData(struct MultiQ* mq, FILE* f) {

    struct Task* temp_task = (struct Task*)malloc(sizeof(struct Task));
    while (fscanf(f, "%d%*c%d", &(temp_task->TaskID), &(temp_task->priority)) != EOF) {
        // read the next element and store into the temp variable.
        // insert temp into the linked list.
        addMQ(mq, temp_task);
    }
    return mq;
}

struct MultiQ* testDel(struct MultiQ* mq, int num) {
    for (int i=0; i<num; i++) 
        mq = delNextMQ(mq);
    return mq;
}