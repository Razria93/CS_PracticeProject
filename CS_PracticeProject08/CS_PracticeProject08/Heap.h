#pragma once
#include <iostream>
#include <climits>

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
		int parent_idx = get_parent(invalue_idx);

		while (invalue_idx != parent_idx && InValue < Base[parent_idx])
		{
			Base[invalue_idx] = Base[parent_idx];
			Base[parent_idx] = InValue;

			invalue_idx = parent_idx;
			parent_idx = get_parent(invalue_idx);
		}
	};

	void pop()
	{
		if (empty())
		{
			std::cout << "[NOTE] pop is invalid (empty)." << '\n';
			return;
		}

		int last_idx = Size - 1;
		int invalue_idx = 0;
		int target_idx = 0;
		int L_chlid_idx = get_L_child(invalue_idx);
		int R_chlid_idx = get_R_child(invalue_idx);

		Base[0] = Base[last_idx];
		Base[last_idx] = INT_MIN;
		--Size;
		--last_idx;

		while (true)
		{
			if (last_idx < L_chlid_idx) break;

			if (last_idx < R_chlid_idx)
			{
				// L_chlid_idx is valid but R_chlid_idx is invalid
				target_idx = L_chlid_idx;
			}
			else // L_chlid_idx, R_chlid_idx is valid
			{
				target_idx = Base[L_chlid_idx] < Base[R_chlid_idx] ? L_chlid_idx : R_chlid_idx;
			}

			if (Base[invalue_idx] < Base[target_idx]) break;

			int temp = Base[invalue_idx];
			Base[invalue_idx] = Base[target_idx];
			Base[target_idx] = temp;

			invalue_idx = target_idx;
			L_chlid_idx = get_L_child(invalue_idx);
			R_chlid_idx = get_R_child(invalue_idx);
		}
	};

	void clear() {};

private:
	int get_parent(int InValue) { return (InValue - 1) / 2; }
	int get_L_child(int InValue) { return InValue * 2 + 1; }
	int get_R_child(int InValue) { return InValue * 2 + 2; }

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