#pragma once

class MinHeap
{
private:
	int* Base = nullptr;

	int Capacity = 0;
	int Size = 0;

public:
	MinHeap(int InSize)
	{
		Base = new int[InSize];
		Capacity = InSize;
		Size = 0;
	}

	~MinHeap()
	{
		delete[] Base;
		Capacity = 0;
		Size = 0;
	}

public:
	bool empty() { return Size == 0; }
	bool full() { return Size == Capacity; }
	int size() { return Size; }
	int top() { return Base[0]; }

public:
	void push(int InValue) {};
	void pop() {};
	void clear() {};
};