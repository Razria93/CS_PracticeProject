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
		
		for (int i = 0; i < Size; ++i)
		{
			if (!Head) break;

			Node* oldHead = Head;
			Head = Head->Next;

			oldHead->Value = 0;
			oldHead->Next = nullptr;

			delete oldHead;
		}

		Head = nullptr;
		Tail = nullptr;
		Size = 0;
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
};