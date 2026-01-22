#pragma once

#include <cstdio>

struct Node
{
public:
	int Value;
	Node* Left = nullptr;
	Node* Right = nullptr;

public:
	Node() = default;

	Node(int InValue)
		: Value(InValue)
	{
	}
};

class BinarySearchTree
{
public:
	Node* Root = nullptr;
	size_t Size = 0;

public:
	BinarySearchTree() = default;

public:
	bool Insert(int InValue)
	{
		Node* node = new Node;

		node->Value = InValue;
		node->Left = nullptr;
		node->Right = nullptr;

		if (!Root)
		{
			if (Size != 0)
			{
				std::printf("%-15s : %s\n", "Error", "InValid Root. but Size != 0.");
				return false;
			}

			Root = node;
			++Size;

			std::printf("%-15s : NodePtr: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Root", node, node->Value, Size);
			return true;
		}

		// Valid Root
		
		Node* targetNode = Root;
		while (targetNode != nullptr)
		{
			if (node->Value < targetNode->Value)
			{
				if (!targetNode->Left)
				{
					targetNode->Left = node;
					++Size;

					std::printf("%-15s : NodePtr: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Left", node, node->Value, Size);
					return true;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Left;
					continue;
				}
			}
			else if(node->Value > targetNode->Value)
			{
				if (!targetNode->Right)
				{
					targetNode->Right = node;
					++Size;

					std::printf("%-15s : NodePtr: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Right", node, node->Value, Size);
					return true;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Right;
					continue;
				}
			}
			else // node->Value == targetNode->Value
			{
				std::printf("%-15s : %s\n", "Error", "InValue be Duplicated.");
				return false;
			}
		}
	}
};