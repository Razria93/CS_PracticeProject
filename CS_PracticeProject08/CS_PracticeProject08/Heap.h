#pragma once

class Heap
{
private:
	int* Base = nullptr;
	
	int Top = 0;
	
	size_t Capacity = 0;
	size_t Size = 0;

public:
	Heap() = default;

public:
	bool empty() { return Size == 0; }
	size_t size() { return Size; }
	int top() { return Top; }

public:
	void push(int InValue) {};
	void pop() {};
	void clear() {};
};