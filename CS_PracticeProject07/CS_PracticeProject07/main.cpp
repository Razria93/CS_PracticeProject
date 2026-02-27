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

	std::cout << '\n';
	std::cout << "[ ##### Pop Test ##### ]" << '\n';
	queue->pop();
	queue->print();

	queue->pop();
	queue->print();
	
	queue->pop();
	queue->print();

	queue->push(10);
	queue->print();

	queue->push(20);
	queue->print();
	
	queue->push(30);
	queue->print();
	
	queue->push(40);
	queue->print();

	queue->clear();
	queue->print();

	return 0;
}