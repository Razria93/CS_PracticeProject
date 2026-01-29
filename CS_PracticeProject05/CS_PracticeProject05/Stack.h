#pragma once

struct Node
{
	int Value;
	Node* Prev;
	Node* Next;

public:
	Node() = default;
};

class Stack
{
public:
	Node* Base;
	Node* Top;
	size_t Size;

public:
	Stack()
	{
		Base = nullptr;
		Top = nullptr;
		Size = 0;
	}

	~Stack()
	{
		// TODO: Clear
	}

public:
};