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
    // read 2 values:
    // 1. N (int; size of linkedlists)
    // 2. toPrint(optional bool; whether to print linkedlist or not)
    if (!(argc >= 2 && argc <= 3))
    {
        printf("Usage: ./<filename> N [toPrint]\n");
        printf("\tN: size of linkedlist,\n");
        printf("\tPrint: (0/1)whether to print contents of linkedlist.\n");
        return 1;
    }
    char *ch;
    int toPrint = 0; // don't print by default
    long n = strtol(argv[1], &ch, 10);
    if (argc == 3)
    {
        toPrint = strtol(argv[2], &ch, 10);
    }

    struct linkedList *linlist = createCycle(createList(n));
    // print heap space
    printf("heap space: %lld\n", HEAP_SPACE);

    // sanity check
    if (toPrint)
    {
        printListN(linlist, linlist->count);
    }

    //check testcyle
    printf("list is cyclic? %d\n", testCyclic(linlist));

    //free and check heap size
    myfree(linlist, linlist->count * sizeof(struct node));

    return 0;
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