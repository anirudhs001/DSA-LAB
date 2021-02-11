// definition of linkedlist
#include <stdio.h>
// structure definitions
// structure of a linked list node. It contains an element
#ifndef vars
#define vars
struct node
{
    int element;
    struct node *next;
};
/*structure of a linked list / head.
 * It stores the count of number of elements in the list and also a pointer link to the first node of the list.  */
struct linkedList
{
    int count;
    struct node *first;
};
#endif

// FUNCTION DECLARATIONS
void insertFirst(struct linkedList *ll, long ele);
/* inserts a given element at the beginning of the list*/

void printList(struct linkedList *ll);
/* prints all the elements in the list*/
