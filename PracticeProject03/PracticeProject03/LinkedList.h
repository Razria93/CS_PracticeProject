#pragma once

#include <iostream>
#include <typeinfo>

struct Node
{
public:
	int Value = 0;
	Node* Next = nullptr;

public:
	Node()
		: Value(0), Next(nullptr)
	{
	}

	Node(const int InValue)
		: Value(InValue), Next(nullptr)
	{
	}
};

class LinkedList
{
private:
	Node* Head = nullptr;
	Node* Tail = nullptr;
	size_t Size = 0;

public:
	LinkedList()
		: Head(nullptr), Tail(nullptr), Size(0)
	{
		std::printf("[Constructor]\n");
	}

	~LinkedList()
	{
		std::printf("[Destructor]\n");
		Clear();
	}

public:
	size_t Size() const { return Size; }

public:
	bool Empty() { return Size == 0; }

public:
	void Clear()
	{
		std::printf("[Clear]\n");

		for (int i = 0; i < Size; ++i)
		{
			if (!Head) break;

			Node* oldHead = Head;
			Head = Head->Next;

			Delete(oldHead, i);
		}

		Head = nullptr;
		Tail = nullptr;
		Size = 0;
	}

public:
	void Delete(Node* InNode, size_t InIndex)
	{
		if (!InNode) return;

		std::printf("[Delete(Before)]\n");
		PrintNodeData(InNode, InIndex);

		InNode->Value = 0;
		InNode->Next = nullptr;

		std::printf("[Delete(After)]\n");
		PrintNodeData(InNode, InIndex);
		
		delete InNode;
	}

public:
	void PushFront(int InValue)
	{
		std::printf("[PushFront]\n");
		Node* newNode = new Node();

		// Init Push Node
		newNode->Value = InValue;
		newNode->Next = nullptr;

		if (!Head) // Init LinkedList
		{
			Head = newNode;

			if (!Tail)
			{
				Tail = newNode;
			}
		}
		else // Add to LinkedList
		{
			Node* oldHead = Head;

			newNode->Next = oldHead;
			Head = newNode;
		}

		++Size;
	}

	void PushBack(int InValue)
	{
		std::printf("[PushBack]\n");
		Node* newNode = new Node();

		// Init Push Node
		newNode->Value = InValue;
		newNode->Next = nullptr;

		if (!Tail) // Init LinkedList
		{
			Tail = newNode;

			if (!Head)
			{
				Head = newNode;
			}
		}
		else  // Add to LinkedList
		{
			Node* oldTail = Tail;

			oldTail->Next = newNode;
			Tail = newNode;
		}

		++Size;
	}

public:
	void PopFront()
	{
		if (!Head) return;

		std::printf("[PopFront]\n");

		if (Size <= 1) Clear();

		Node* oldHead = Head;

		Head = oldHead->Next ? oldHead->Next : nullptr;
		--Size;

		Delete(oldHead, 0);
	}

public:
	static void PrintLinkedListData(LinkedList* InLinkedList)
	{
		std::printf("========================================\n");
		std::printf("[PrintLinkedListData]\n");

		if (InLinkedList == nullptr)
		{
			std::printf("----------------------------------------\n");
			std::printf("%-15s : %s\n", "LinkedList", "nullptr");
			std::printf("========================================\n");
			return;
		}

		std::printf("----------------------------------------\n");
		std::printf("%-15s : %p\n", "InLinkedList", (void*)InLinkedList);
		std::printf("%-15s : %p\n", "Head", (void*)InLinkedList->Head);
		std::printf("%-15s : %p\n", "Tail", (void*)InLinkedList->Tail);
		std::printf("%-15s : %zu\n", "Size", InLinkedList->Size);
		std::printf("========================================\n");
	}

	static void PrintNodeData(const Node* InNode, size_t InIndex)
	{
		std::printf("========================================\n");
		std::printf("[%s]\n", "PrintNodeData");

		if (InNode == nullptr)
		{
			std::printf("----------------------------------------\n");
			std::printf("%-15s : %s\n", "Node", "nullptr");
			std::printf("========================================\n");
			return;
		}

		std::printf("----------------------------------------\n");
		std::printf("[%s]\n", "PrintNodeData");
		std::printf("%-15s : %zu\n", "NodeIndex", InIndex);
		std::printf("%-15s : %p\n", "NodePointer", (void*)InNode);
		std::printf("%-15s : %s\n", "ValueType", typeid(int).name());
		std::printf("%-15s : %d\n", "Value", (int)InNode->Value);
		std::printf("%-15s : %p\n", "NextNode", (void*)InNode->Next);
		std::printf("========================================\n");
	}

	static void PrintAllNodeData(LinkedList* InLinkedList)
	{
		std::printf("========================================\n");
		std::printf("[%s]\n", "PrintAllNodeData");

		if (InLinkedList == nullptr)
		{
			std::printf("%-15s : %s\n", "LinkedList", "nullptr");
			std::printf("========================================\n");
			return;
		}

		if (InLinkedList->Head == nullptr)
		{
			std::printf("%-15s : %p\n", "LinkedList", (const void*)InLinkedList);
			std::printf("%-15s : %s\n", "Head", "nullptr");
			std::printf("========================================\n");
			return;
		}

		const Node* printNode = InLinkedList->Head;
		std::size_t index = 0;

		while (printNode != nullptr)
		{
			PrintNodeData(printNode, index);
			printNode = printNode->Next;
			++index;
		}
		std::printf("========================================\n");
	}
};