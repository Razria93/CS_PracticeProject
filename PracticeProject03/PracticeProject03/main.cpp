#include <iostream>

#include "LinkedList.h"

int main()
{
	std::printf("## Init ##\n");
	LinkedList* linkedList = new LinkedList;
	LinkedList::PrintLinkedListData(linkedList);
	
	std::printf("## PushBack ##\n");
	linkedList->PushBack(100);
	linkedList->PushBack(200);
	linkedList->PushBack(300);
	LinkedList::PrintLinkedListData(linkedList);

	delete linkedList;
	return 0;
}