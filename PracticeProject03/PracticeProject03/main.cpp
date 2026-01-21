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

	std::printf("## Clear ##\n");
	linkedList->Clear();
	// LinkedList::PrintLinkedListData(linkedList);
	// LinkedList::PrintAllNodeData(linkedList);

	delete linkedList;
	return 0;
}