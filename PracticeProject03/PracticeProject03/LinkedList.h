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
	}

	~LinkedList()
	{
		Clear();
	}

public:
	size_t GetSize() const { return Size; }

public:
	bool Empty() { return Size == 0; }

public:
	void Clear()
	{
		for (size_t i = 0; i < Size; ++i)
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

		// std::printf("[Delete(Before)]\n");
		// PrintNodeData(InNode, InIndex);

		InNode->Value = 0;
		InNode->Next = nullptr;

		// std::printf("[Delete(After)]\n");
		// PrintNodeData(InNode, InIndex);

		delete InNode;
	}

public:
	void PushFront(int InValue)
	{
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
	bool PopFront()
	{
		if (!Head) return false;

		if (Size <= 1)
		{
			Clear();
			return true;
		}

		Node* oldHead = Head;
		size_t oldHeadIdx = 0;

		size_t newSize = Size - 1;

		Node* afterNode = oldHead->Next;
		if (!afterNode)
		{
			std::printf("%-15s : Pointer: %p | Index: %d\n", "Error", afterNode, 0);
			return false;
		}
		else
		{
			Head = afterNode;
			Size = newSize;

			Delete(oldHead, oldHeadIdx);
			return true;
		}
		return false; // Undefined
	}

public:
	bool PopBack()
	{
		if (!Head) return false;
		if (!Tail) return false;

		if (Size <= 1)
		{
			Clear();
			return true;
		}

		Node* oldTail = Tail;
		size_t oldTailIdx = Size - 1;

		size_t newSize = Size - 1;

		Node* beforeNode = nullptr;
		for (size_t i = 0; i < newSize; ++i)
		{
			if (i == 0) // Init
			{
				if (!Head) return false;

				beforeNode = Head;
				continue;
			}

			// UpdateNextNode
			Node* curNode = beforeNode->Next;

			// Validate
			if (!curNode)
			{
				std::printf("%-15s : Pointer: %p | Index: %zd\n", "Error", curNode, i);
				return false;
			}

			// Check Index
			if (i < (newSize - 1))
			{
				beforeNode = curNode;
				curNode = nullptr;
				continue;
			}
			else // Last index (i == (newSize - 1))
			{
				curNode->Next = nullptr;

				Tail = curNode;
				Size = newSize;

				Delete(oldTail, oldTailIdx);
				return true;
			}
		}
		return false; // Undefined
	}

public:
	bool Contain(size_t InIndex)
	{
		if (!Head) return false;
		if (InIndex >= Size) return false;

		if (InIndex == 0) return true; // Head is Valid

		Node* beforeNode = nullptr;
		for (size_t i = 0; i <= InIndex; ++i)
		{
			if (i == 0) // Init
			{
				if (!Head) return false;

				beforeNode = Head;
				continue;
			}

			// UpdateNextNode
			Node* curNode = beforeNode->Next;

			// Validate
			if (!curNode)
			{
				std::printf("%-15s : Pointer: %p | Index: %zd\n", "Error", curNode, i);
				return false;
			}

			// Check Index
			if (i < (InIndex))
			{
				beforeNode = curNode;
				curNode = nullptr;
				continue;
			}
			else // Last index (i == newSize)
			{
				std::printf("%-15s : Pointer: %p | Index: %zd\n", "Valid", curNode, InIndex);
				return true;
			}
		}
		return false; // Undefined
	}

public:
	Node* Find(int InValue)
	{
		Node* beforeNode = nullptr;
		Node* curNode = nullptr;

		for (int i = 0; i < Size; ++i)
		{
			if (i == 0)
			{
				curNode = Head;
			}
			else
			{
				curNode = beforeNode->Next;
			}

			// Validate
			if (!curNode) return nullptr;

			// Check
			if (curNode->Value == InValue)
			{
				return curNode;
			}
			else // curNode->Value != InValue
			{
				beforeNode = curNode;
				curNode = nullptr;
				continue;
			}
		}
		return nullptr; // Undefined
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
		std::printf("----------------------------------------\n");
		std::printf("[%s]\n", "PrintNodeData");

		if (InNode == nullptr)
		{
			std::printf("%-15s : %s\n", "Node", "nullptr");
			std::printf("----------------------------------------\n");

			return;
		}

		std::printf("%-15s : %zu\n", "NodeIndex", InIndex);
		std::printf("%-15s : %p\n", "NodePointer", (void*)InNode);
		std::printf("%-15s : %s\n", "ValueType", typeid(int).name());
		std::printf("%-15s : %d\n", "Value", (int)InNode->Value);
		std::printf("%-15s : %p\n", "NextNode", (void*)InNode->Next);
		std::printf("----------------------------------------\n");
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