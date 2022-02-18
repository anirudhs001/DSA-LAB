#include "stdio.h"
#include "book.h"
#include "hashTable.h"
#include <wchar.h>
#include <locale.h>

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