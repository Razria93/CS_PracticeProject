#include <iostream>

#include "LinkedList.h"

int main()
{
	std::printf("## Init ##\n");
	LinkedList* linkedList = new LinkedList;
	// LinkedList::PrintLinkedListData(linkedList);
	
	std::printf("## PushBack ##\n");
	linkedList->PushBack(100);
	linkedList->PushBack(200);
	linkedList->PushBack(300);
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	std::printf("## PushFront ##\n");
	linkedList->PushFront(400);
	linkedList->PushFront(500);
	linkedList->PushFront(600);
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	std::printf("## PopFront ##\n");
	std::printf("%-15s : %-5s\n", "bPopFront", linkedList->PopFront() ? "true" : "false");
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	std::printf("## PopBack ##\n");
	std::printf("%-15s : %-5s\n", "bPopBack", linkedList->PopBack() ? "true" : "false");
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	// std::printf("## Contain_Case01##\n");
	// size_t targetIdx_0 = 1;
	// std::printf("%-15s : %-5s (TargetIdx: %zd)\n", "bContain", linkedList->Contain(targetIdx_0) ? "true" : "false", targetIdx_0);
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	// std::printf("## Contain_Case02##\n");
	// size_t targetIdx_1 = 5;
	// std::printf("%-15s : %-5s (TargetIdx: %zd)\n", "bContain", linkedList->Contain(targetIdx_1) ? "true" : "false", targetIdx_1);
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	// std::printf("## Find##\n");
	// int targetValue = 100;
	// Node* findNode = linkedList->Find(targetValue);
	// 
	// std::printf("%-15s : %-5s\n", "IsValid", findNode ? "Valid" : "InValid");
	// 
	// if(findNode)
	// 	std::printf("%-15s : CurPointer: %p | Value: %d | NextPointer: %p\n", "Find", findNode, findNode->Value, findNode->Next);
	// 
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	std::printf("## Insert_after##\n");
	size_t targetIdx = 3;
	int targetValue = 1000;
	std::printf("%-15s : %-5s\n", "Insert_after", linkedList->Insert_after(targetIdx, targetValue) ? "true" : "false");
	LinkedList::PrintLinkedListData(linkedList);
	LinkedList::PrintAllNodeData(linkedList);

	std::printf("## Clear ##\n");
	linkedList->Clear();
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	delete linkedList;
	return 0;
}