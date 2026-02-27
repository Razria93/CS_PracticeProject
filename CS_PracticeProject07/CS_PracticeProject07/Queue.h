#pragma once
#include <iostream>

class Queue
{
private:
	int* Base = nullptr;
	int Front = 0;
	int Rear = 0;

	size_t Capacity = 0;
	size_t Size = 0;

public:
	Queue(int InSize)
	{
		Base = new int[InSize] {};
		Size = 0;
		Capacity = InSize;
	}

public:
	~Queue()
	{
		delete[] Base;
		Size = 0;
		Capacity = 0;
	}

public:
	// State
	bool empty() { return Size == 0; }
	bool full() { return Size == Capacity; }

	// Size
	size_t size() { return Size; }

	// Iterator
	int* front() { return Base + Front; }
	int* back() { return Base + Rear; }

public:
	void push(int InValue)
	{
		if (full())
		{
			std::cout << "[NOTE] push(" << InValue << ")" << " is invalid." << '\n';
			return;
		}

		Base[Rear] = InValue;
		Rear = (Rear + 1) % Capacity;
		++Size;
	};

	void pop()
	{
		if (empty())
			std::cout << "[NOTE] pop is invalid (empty)." << '\n';

		Base[Front] = NULL;
		Front = (Front + 1) % Capacity;
		--Size;
	};
	void clear() {};

public:
	void print()
	{
		std::cout << "=== Queue Print ===" << '\n';
		std::cout << "[Base Info]" << '\n';
		std::cout << "- Capacity :" << Capacity << '\n';
		std::cout << "- Size :" << Size << '\n';
		std::cout << "- Front_idx :" << Front << '\n';
		std::cout << "- Rear_idx :" << Rear << '\n';

		std::cout << '\n';
		std::cout << "[Idx and Value]" << '\n';
		
		if (empty())
			std::cout << "[NOTE] Queue is empty." << '\n';
		else
		{
			for (size_t i = 0; i < Capacity; ++i)
			{
				std::cout << "idx_" << i << ": " << Base[i] << '\n';
			}
		}

		std::cout << "===================" << '\n';
	}
};