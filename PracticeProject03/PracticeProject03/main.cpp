#include <iostream>

#include "LinkedList.h"

int main()
{
	std::printf("## Init ##\n");
	LinkedList* linkedList = new LinkedList;
	LinkedList::PrintLinkedListData(linkedList);

	delete linkedList;
	return 0;
}