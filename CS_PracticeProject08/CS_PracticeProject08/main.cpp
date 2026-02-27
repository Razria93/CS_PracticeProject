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

	for (int i = 0; i < 5; ++i)
	{
		minHeap->pop();
	}

	minHeap->print();

	std::cout << "[Test top()]" << '\n';
	std::cout << "Top is [" << minHeap->top() << "] in MinHeap." << '\n';

	minHeap->clear();
	minHeap->print();

	return 0;
}