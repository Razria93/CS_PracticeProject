#pragma once

#include <cstdio>

enum ECacheDirection
{
	None = 0,
	Left,
	Right,
};

struct Node
{
public:
	int Value;
	Node* Parent = nullptr;
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

	~BinarySearchTree()
	{
		std::printf("\n[Destructor]\n");
		Clear();
	}

public:
	size_t GetSize() const { return Size; }
	bool Empty() const { return Size == 0; }

public:
	bool Clear()
	{
		Node* targetNode = Root;
		ECacheDirection cacheDirection = ECacheDirection::None;

		while (targetNode != nullptr)
		{
			if (targetNode->Left)
			{
				cacheDirection = ECacheDirection::Left;
				targetNode = targetNode->Left;
			}
			else if (targetNode->Right)
			{
				cacheDirection = ECacheDirection::Right;
				targetNode = targetNode->Right;
			}
			else
			{
				Node* parent = targetNode->Parent;

				if (!parent)
				{
					if (targetNode != Root)
					{
						std::printf("%-15s : %s\n", "Error", "InValid Parent.");
						return false;
					}

					// targetNode == Root

					Delete(Root);

					Root = nullptr;
					Size = 0;

					std::printf("%-15s : Root: %p | Size: %-5zd\n", "Complete_Clear", Root, Size);
					return true;
				}

				// Valid Parent
				Delete(targetNode);
				--Size;

				std::printf("%-15s : Target: %p | Size: %-5zd\n", "Complete_Delete", targetNode, Size);

				if (cacheDirection == ECacheDirection::Left)
				{
					std::printf("%-15s : Parent->Left: %p\n", "Child_Before", parent->Left);

					parent->Left = nullptr;
					targetNode = parent;

					std::printf("%-15s : Parent->Left: %p\n\n", "Child_After", parent->Left);
				}
				else if (cacheDirection == ECacheDirection::Right)
				{
					std::printf("%-15s : Parent->Right: %p\n", "Child_Before", parent->Right);

					parent->Right = nullptr;
					targetNode = parent;

					std::printf("%-15s : Parent->Right: %p\n\n", "Child_After", parent->Right);
				}
				else
				{
					targetNode = parent;
				}
			} // else
		} // while

		std::printf("%-15s : %s\n", "InValid", "InValid Node in BST.");
		return false;
	}

	void Delete(Node* InNode)
	{
		std::printf("%-15s : Parent: %p | Node: %p | NodeValue: %-5d\n", "Delete_Before", InNode->Parent, InNode, InNode->Value);

		InNode->Parent = nullptr;
		InNode->Left = nullptr;
		InNode->Right = nullptr;

		std::printf("%-15s : Parent: %p | Node: %p | NodeValue: %-5d\n", "Delete_After", InNode->Parent, InNode, InNode->Value);

		delete InNode;
	}

public:
	bool Insert(int InValue)
	{
		Node* node = new Node;

		node->Value = InValue;
		node->Parent = nullptr;
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

			std::printf("%-15s : Parent: %p | Node: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Root", node->Parent, node, node->Value, Size);
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
					node->Parent = targetNode;
					++Size;

					std::printf("%-15s : Parent: %p | Node: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Left", node->Parent, node, node->Value, Size);
					return true;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Left;
					continue;
				}
			}
			else if (node->Value > targetNode->Value)
			{
				if (!targetNode->Right)
				{
					targetNode->Right = node;
					node->Parent = targetNode;
					++Size;

					std::printf("%-15s : Parent: %p | Node: %p | NodeValue: %-5d | Size: %zd\n", "Insert_Right", node->Parent, node, node->Value, Size);
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
		} // while

		std::printf("%-15s : %s\n", "Error", "Undefined.");
		return false;
	} // Insert
};