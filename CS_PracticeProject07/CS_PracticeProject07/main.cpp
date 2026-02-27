#include <iostream>
#include "Queue.h"

int main()
{
	Queue* queue = new Queue(10);

	std::cout << "[ ##### Push Test ##### ]" << '\n';
	queue->push(1);
	queue->push(2);
	queue->push(3);
	queue->push(4);
	queue->push(5);
	queue->push(6);
	queue->push(7);
	queue->push(8);
	queue->push(9);
	queue->push(10);
	queue->push(11);
	queue->print();

	return 0;
}