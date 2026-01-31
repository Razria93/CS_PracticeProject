#include <iostream>
#include "HashTable.h"

void PrintFindResult(size_t InKey, int InValue, Node* InResult)
{
	printf("[%s/%s] %s: %s | key: %zd | value: %d\n", "Note", "main", "IsFind", InResult ? "Valid" : "InValid", InKey, InValue);

	if (InResult)
	{
		printf("[%s/%s] %s: pointer: %p | key: %zd | value: %d\n", "Note", "main", "Find Result", InResult, InResult->Key, InResult->Value);
	}
}

int main()
{
	HashTable* hashTable = new HashTable;
	hashTable->Initialize(10);

	printf("\n[Insert]\n");
	hashTable->Insert(1, 100);
	hashTable->Insert(2, 200);
	hashTable->Insert(3, 300);
	hashTable->Insert(2, 300);
	hashTable->Insert(2, 300);

	printf("\n[Find]\n");
	Node* find0 = hashTable->Find(3, 300);
	PrintFindResult(3, 100, find0);

	printf("\n");
	Node* find1 = hashTable->Find(2, 300);
	PrintFindResult(2, 300, find1);

	printf("\n");
	Node* find2 = hashTable->Find(1, 300);
	PrintFindResult(1, 300, find2);

	return 0;
}