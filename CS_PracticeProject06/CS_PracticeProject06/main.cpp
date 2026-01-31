#include <iostream>
#include "HashTable.h"

int main()
{
	HashTable* hashTable = new HashTable;
	hashTable->Initialize(10);
	hashTable->Insert(100);
	hashTable->Insert(200);
	hashTable->Insert(300);
	hashTable->Insert(300);

	Node* find0 = hashTable->Find(300);
	if (find0)
	{
		printf("[%s/%s] %s: %d\n", "Note", "main", "Find Value", find0->Value);
	}

	return 0;
}