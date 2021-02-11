// Hare and tortoise implementation of testCyclic
#include "cycle.h"

int testCyclic(struct linkedList *ll)
{
    struct node *tort = ll->first;
    struct node *hare = ll->first;

    while (hare != NULL && tort != NULL)
    {
        // move both ahead
        tort = tort->next;
        hare = hare->next;
        if (hare == NULL)
            break;
        hare = hare->next;

        // check if same
        if (tort == hare)
            return 1;
    }
    return 0;
}