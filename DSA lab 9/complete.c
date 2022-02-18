
// ALL THE CODE IN A SINGLE FILE(INCLUDING HEADER FILES)

#include "stdio.h"
#include "wchar.h"
#include "stdlib.h"
#include "string.h"
#include <locale.h>

#ifndef b
#define b
struct Book {
    wchar_t ** words;
    long size;
};
#endif

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
#define MAXSIZE 1000


// hash a single word
long Hash(wchar_t* string, long baseNumber, long tableSize) {
    long sum = 0;
    for (int i = 0; string[i] != '\0' && i < MAXSIZE; i++) {
        sum += string[i];
    }
    return ( sum % baseNumber ) % tableSize;
}


// count the number of collisions in array book
long Collisions(struct Book book, long baseNumber, long tableSize) {
    long collisions = 0;
    int* seenHashes = calloc(tableSize, sizeof(int));
    for (long i = 0; i < book.size; i++) {
        long hash = Hash(book.words[i], baseNumber, tableSize);
        // first check if this index exists in seenHashes
        if (seenHashes[hash] == 1)
            collisions++;
        else
            seenHashes[hash] = 1;
    }
    return collisions;
}

// parse through file and save all allowed words
struct Book Parser(char* filePath) {

    struct Book book = {NULL, 0};

    wchar_t word[1000];
    wchar_t** words = (wchar_t**)malloc(100 * sizeof(wchar_t*));
    FILE* fptr = fopen(filePath, "rb");
    if (fptr == NULL)
    {
        printf("File does not exist\n");
        return book;
    } 
    int wordAllowed = 1;
    long i = 0;
    while (fwscanf(fptr, L"%ls", word) != EOF) {

        // NOTE: in our lab section, we were told that only allowed words(i.e. 
        // words containing only alphabets) should be added. This leads to a lower word 
        // count(of ~22k). If we need to consider all space seperated words, remove the
        // mentioned code:

        /////////////////////////////
        // REMOVE FROM HERE
        wordAllowed = 1;
        for (int j = 0; j < wcslen(word); j++) {
            if (!((word[j] >= 'a' && word[j] <= 'z') || (word[j] >= 'A' && word[j] <= 'Z'))) {
                wordAllowed = 0;
                break;
            }
        }
        if ( wordAllowed != 1 ) 
            continue;
        // REMOVE TILL HERE 
        ///////////////////////////////
        
        // add word in array 
        if (i >= sizeof(book)/sizeof(wchar_t*)) {
            words = (wchar_t**)realloc(words, sizeof(wchar_t*)*(i+101));
        }
        words[i] = (wchar_t*)malloc(sizeof(wchar_t) * (wcslen(word) + 1));
        wcscpy(words[i], word);
        i++;
    }
    fclose(fptr); //done reading. close
    // print size of book
    printf("Number of words in book:%ld\n", i);

    // save booksize
    book.words = words;
    book.size = i;
    return book;
}


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



int main(int argc, wchar_t* argv) {

    setlocale(LC_ALL, "en_US.UTF-8");
    // count number of words
    struct Book book = Parser("aliceinwonderland.txt");
    // Test hash function
    wchar_t word[] = L"hello";
    printf("Hash for %ls = %ld\n", word, Hash(word, 5003, 5000));
    // Profiling
    long c = Collisions(book, 5003, 5000);
    printf("number of collisions :%ld\n", c);

    HashTable* myHashTable = newHashTable(50000, 50021);
    printf("%d\n", insertAll(book.words, book.size, myHashTable));
	printf("%d\n", lookup(book.words, 4, myHashTable)->count);
	printf("%d\n", lookupAll(book.words, book.size, myHashTable,0.1));
	printf("%d\n",myHashTable->tableSize);
	return 0;
}