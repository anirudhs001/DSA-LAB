#include "stdlib.h"
#include "book.h"
#include "wchar.h"

#ifndef nd
#define nd
typedef struct node Node;
struct node
{
	int firstindex;
	int count;
	Node* next;
};
#endif

#ifndef ht
#define ht
typedef struct hashtable HashTable;
struct hashtable{
	int elementCount;
	int insertionCost;
	int queryingCost;
	int tableSize;
	int baseNumber;
	Node** table;
};
#endif

Node* newNode();
HashTable* newHashTable(int tableSize,int baseNumber);
void insertHash(wchar_t** arr, long index, HashTable* hTable);
int insertAll(wchar_t** arr, long len, HashTable* hTable);
Node* lookup(wchar_t** arr, long index, HashTable* htable);
int lookupAll(wchar_t** arr, long size, HashTable* htable, double m);