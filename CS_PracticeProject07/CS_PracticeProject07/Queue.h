#pragma once

class Queue
{
private:
	int* Base = nullptr;
	int Front = 0;
	int Rear = 0;

	size_t Capacity = 0;
	size_t Size = 0;

public:
	Queue() = default;

public:
	// State
	bool empty() { return Size == 0; }
	bool full() { return Size == Capacity; }
	
	// Size
	int size() { return Size; }
	
	// Iterator
	int* front() { return Base + Front; }
	int* back() { return Base + Rear; }

public:
	void push(int InValue) {};
	void pop() {};
	void clear() {};
};