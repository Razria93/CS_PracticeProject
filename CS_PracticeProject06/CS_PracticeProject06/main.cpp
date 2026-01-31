#include <iostream>
#include "HashTable.h"

void PrintContainResult(size_t InKey, bool InResult)
{
	printf("[%s/%s] %s: %s | key: %zd\n", "Note", "main", "IsContain", InResult ? "Contain" : "Not Contain", InKey);
}

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
	hashTable->Insert(11, 100);

	printf("\n[Contain]\n");
	bool contain0 = hashTable->Contain(0);
	PrintContainResult(0, contain0);

	printf("\n");
	bool contain1 = hashTable->Contain(1);
	PrintContainResult(1, contain1);

	printf("\n");
	bool contain2 = hashTable->Contain(2);
	PrintContainResult(2, contain2);

	printf("\n[Find]\n");
	Node* find0 = hashTable->Find(3, 300);
	PrintFindResult(3, 100, find0);

	printf("\n");
	Node* find1 = hashTable->Find(2, 300);
	PrintFindResult(2, 300, find1);

	printf("\n");
	Node* find2 = hashTable->Find(1, 300);
	PrintFindResult(1, 300, find2);

	printf("\n");
	Node* find3 = hashTable->Find(1, 100);
	PrintFindResult(1, 100, find3);

	printf("\n");
	Node* find4 = hashTable->Find(11, 100);
	PrintFindResult(11, 100, find4);

	return 0;
}