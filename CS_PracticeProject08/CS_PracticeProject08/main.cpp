#include <iostream>
#include "Heap.h"

int main()
{
	MinHeap* minHeap = new MinHeap(10);
	for (int i = 0; i <= 10; ++i)
	{
		minHeap->push(10 - i);
	}

	minHeap->print();


	return 0;
}