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
			printf("[%s/%s]%-20s\n", "Error", "Pop", "InValid popable node.");
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

			printf("[%s/%s]%-20s\n", "Note", "Pop", "Pop Base. No more Value.");
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
			printf("[%s/%s]%-20s\n", "Error", "Pop", "Undefined.");
			return;
		}

		printf("[%s/%s]%-20s\n", "Error", "Pop", "Undefined.");
		return;
	}

public:
	bool Peek(int& OutValue)
	{
		if (!Base || !Top)
		{
			printf("[%s/%s]%-20s\n", "Error", "Peek", "InValid peekable node.");
			return false;
		}

		OutValue = Top->Value;
		return true;
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

				printf("[%s/%s]%-20s\n", "Note", "Clear", "Complete Clear.");
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
				printf("[%s/%s]%-20s\n", "Error", "Clear", "Undefined.");
				return;
			}
		}

		printf("[%s/%s]%-20s\n", "Error", "Clear", "Disable Clear.");
		return;
	}
};