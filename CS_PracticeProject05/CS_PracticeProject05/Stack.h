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
		Clear();
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

public:
	void Pop()
	{
		if (!Base || !Top)
		{
			printf("[%s]%-20s", "Error", "InValid popable node");
			return;
		}

		if (Top == Base)
		{
			Top->Value = 0;
			Top->Next = nullptr;
			Top->Prev = nullptr;

			delete Top;

			Base = nullptr;
			Top = nullptr;
			Size = 0;

			printf("[%s]%-20s", "NOTE", "Base Pop");
			return;
		}

		Node* nextTopNode = Top->Prev;

		Top->Value = 0;
		Top->Next = nullptr;
		Top->Prev = nullptr;

		delete Top;

		--Size;

		if (nextTopNode)
		{
			nextTopNode->Next = nullptr;
			Top = nextTopNode;
			return;
		}
		else
		{
			Top = nullptr;
			printf("[%s]%-20s", "Error", "Undefined");
			return;
		}

		printf("[%s]%-20s", "Error", "Undefined");
		return;
	}

public:
	void Clear()
	{
		while (Top)
		{
			if (Top == Base)
			{
				Top->Value = 0;
				Top->Next = nullptr;
				Top->Prev = nullptr;

				delete Top;

				Base = nullptr;
				Top = nullptr;
				Size = 0;

				printf("[%s]%-20s", "Complete", "Clear");
				return;
			}

			Node* nextTopNode = Top->Prev;

			Top->Value = 0;
			Top->Next = nullptr;
			Top->Prev = nullptr;

			delete Top;

			--Size;

			if (nextTopNode)
			{
				nextTopNode->Next = nullptr;
				Top = nextTopNode;
				return;
			}
			else
			{
				Top = nullptr;
				printf("[%s]%-20s", "Error", "Undefined");
				return;
			}
		}

		printf("[%s]%-20s", "Error", "Undefined");
		return;
	}
};