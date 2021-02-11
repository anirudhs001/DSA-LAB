#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"
#include "lib.h"
#include "cycle.h"

extern long long int HEAP_SPACE;

struct linkedList *createList(long n);
struct linkedList *createCycle(struct linkedList *ll);

int main(int argc, char const *argv[])
{
    long n = (long)1.5e6; // 1.5 million
    struct linkedList *linlist = createList(n);
    // print heap space
    printf("heap space: %lld\n", HEAP_SPACE);

    //new list with createCycle
    struct linkedList *linlist2 = createList(n);
    linlist2 = createCycle(linlist2);

    // sanity check
    // printListN(linlist, linlist->count);
    // printListN(linlist2, linlist2->count); 

    //check testcyle
    printf("first list is cyclic? %d\n", testCyclic(linlist));
    printf("second list is cyclic? %d\n", testCyclic(linlist2));

    myfree(linlist, linlist->count * sizeof(struct node));
    myfree(linlist2, linlist2->count * sizeof(struct node));
}

struct linkedList *createList(long n)
{
    struct linkedList *templist = (struct linkedList *)myalloc(sizeof(struct linkedList));
    templist->count = 0;
    templist->first = NULL;
    srand(time(0));
    for (int i = 0; i < n; i++)
        insertFirst(templist, rand());
    return templist;
}

struct linkedList *createCycle(struct linkedList *ll)
{
    srand(time(0));
    int toss = rand() % 2;
    // only for testing testCycle
    // toss = 1;
    if (toss)
    {
        int r = rand() % ll->count;
        // address of rth node
        struct node *rnode = NULL;
        // temp node to iterate through the linked list
        struct node *temp_node = ll->first;
        for (int i = 0; i < ll->count; i++)
        {
            if (i == r)
                rnode = temp_node;
            if (i == ll->count - 1)
                temp_node->next = rnode;

            temp_node = temp_node->next;
        }
    }
    return ll;
}