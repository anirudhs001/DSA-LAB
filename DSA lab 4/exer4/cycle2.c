// Link reversal implementation of testCyclic 
#include"cycle.h"

int testCyclic(struct linkedList *ll)
{
    struct node *prev = NULL, *curr = NULL, *next = NULL;
    curr = ll->first;
    if (curr == NULL) 
        return 0;

    next = curr->next;
    if (curr == NULL) 
        return 0;

    while (next != NULL)
    {
        // reverse direction
        curr->next = prev;
        // move ahead
        prev = curr;
        curr = next;
        next = next->next;
    }
    if (ll->first == curr) // got back where we started
        return 1;
    ll->first = curr; // update head
    return 0;
}