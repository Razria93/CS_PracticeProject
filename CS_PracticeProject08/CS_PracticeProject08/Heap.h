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
	void push(int InValue)
	{
		if (full())
		{
			std::cout << "[NOTE] push(" << InValue << ")" << " is invalid." << '\n';
			return;
		}

		Base[Size] = InValue;
		++Size;

		int invalue_idx = Size - 1;
		int parent_idx = idx_parent(invalue_idx);

		while (invalue_idx != parent_idx && InValue < Base[parent_idx])
		{
			Base[invalue_idx] = Base[parent_idx];
			Base[parent_idx] = InValue;

			invalue_idx = parent_idx;
			parent_idx = idx_parent(invalue_idx);
		}
	};

	void pop() {};
	void clear() {};

private:
	int idx_parent(int InValue) { return (InValue - 1) / 2; }
	int idx_L_child(int InValue) { return InValue * 2 + 1; }
	int idx_R_child(int InValue) { return InValue * 2 + 2; }

public:
	void print()
	{
		std::cout << "=== Queue Print ===" << '\n';
		std::cout << "[Base Info]" << '\n';
		std::cout << "- Capacity :" << Capacity << '\n';
		std::cout << "- Size :" << Size << '\n';

		std::cout << '\n';
		std::cout << "[Idx and Value]" << '\n';

		if (empty())
			std::cout << "[NOTE] Queue is empty." << '\n';
		else
		{
			for (int i = 0; i < Capacity; ++i)
			{
				std::cout << "idx_" << i << ": " << Base[i] << '\n';
			}
		}

		std::cout << "===================" << '\n';
	}
};