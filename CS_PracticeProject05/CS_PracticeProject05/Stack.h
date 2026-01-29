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
	void Push(int InValue)
	{
		Node* newNode = new Node;

		if (!Base || !Top)
		{
			newNode->Value = InValue;
			newNode->Prev = nullptr;
			newNode->Next = nullptr;

			Base = newNode;
			Top = newNode;

		}
		else // Valid Base
		{
			Node* oldTopNode = Top;

			newNode->Value = InValue;
			newNode->Prev = oldTopNode;
			newNode->Next = nullptr;

			oldTopNode->Next = newNode;

			Top = newNode;
		}

		++Size;
		return;
	}

};