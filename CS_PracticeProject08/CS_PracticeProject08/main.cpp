#include <iostream>
#include "Heap.h"

int main()
{
	MinHeap* minHeap = new MinHeap(10);
	minHeap->push(10);
	minHeap->print();

	minHeap->push(9);
	minHeap->print();

	minHeap->push(8);
	minHeap->print();

	minHeap->push(7);
	minHeap->print();
	
	minHeap->push(6);
	minHeap->print();
	
	minHeap->push(5);
	minHeap->print();
	
	minHeap->push(4);
	minHeap->print();
	
	minHeap->push(3);
	minHeap->print();
	
	minHeap->push(2);
	minHeap->print();
	
	minHeap->push(1);
	minHeap->print();
	
	minHeap->push(0);
	minHeap->print();

	std::cout << "Top is " << minHeap->top();

	return 0;
}