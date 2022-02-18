#include "hashTable.h"
#include "string.h"

Node *newNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->firstindex = 0;
    node->count = 0;
    node->next = NULL;
    return node;
}

HashTable *newHashTable(int tableSize, int baseNumber)
{
    HashTable *hashT = (HashTable *)malloc(sizeof(HashTable));
    hashT->tableSize = tableSize;
    hashT->baseNumber = baseNumber;
    hashT->table = (Node **)malloc(sizeof(Node *) * tableSize);
    for (int i = 0; i < tableSize; i++)
    {
        hashT->table[i] = NULL;
    }
    hashT->elementCount = 0;
    hashT->insertionCost = 0;
    hashT->queryingCost = 0;
    return hashT;
}

void insertHash(wchar_t **arr, long index, HashTable *htable)
{
    long hash = Hash(arr[index], htable->baseNumber, htable->tableSize);
    if (htable->table[hash] == NULL) // table contains no nodes
    {
        htable->table[hash] = newNode();
        htable->table[hash]-> firstindex = index;
        htable->table[hash]-> count = 1;
        htable->tableSize++;
    }
    else
    {
        Node *curr = htable->table[hash];
        while (curr->next != NULL && (wcscmp(arr[index], arr[curr->firstindex])))
        {
            htable->insertionCost++;
            curr = curr->next;
        }
        if (!(wcscmp(arr[index], arr[curr->firstindex])))
        {
            curr->count++;
        }
        else
        {
            curr->next = newNode();
            curr->next->firstindex = index;
            curr->next->count = 1;
            htable->tableSize++;
        }
    }
}

int insertAll(wchar_t** arr, long size, HashTable* htable){
	for(int i=0;i<size;i++){
		insertHash(arr, i, htable);
	}
	return htable->insertionCost;
}

Node* lookup(wchar_t** arr, long index, HashTable* htable){
	long hash = Hash(arr[index],htable->baseNumber,htable->tableSize);
	Node* curr = htable->table[hash];
	while(curr && wcscmp(arr[index], arr[curr->firstindex])){
		htable->queryingCost++;
		curr=curr->next;
	} 
	return curr;
}

int lookupAll(wchar_t** arr, long size, HashTable* htable, double m){
	htable->queryingCost=0;
	for(int i=0;i<(int)(m*size);i++){
		lookup(arr,i, htable);
	}
	return htable->queryingCost;
}
