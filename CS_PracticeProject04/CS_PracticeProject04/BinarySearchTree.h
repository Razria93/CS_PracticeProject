#pragma once

#include <cstdio>

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
		bool result = Clear(Root);

		Root = nullptr;
		Size = 0;

		return result;
	}

	bool Clear(Node* InNode)
	{
		if (!InNode)
		{
			return false; // this Node is NULL
		}

		if (Clear(InNode->Left))
		{
			std::printf(
				"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
				"Clear_Left", InNode->Value, InNode, InNode->Left, InNode->Parent);
		}
		else
		{
			std::printf(
				"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
				"InValid_Left", InNode->Value, InNode, InNode->Left, InNode->Parent);
		}

		if (Clear(InNode->Right))
		{
			std::printf(
				"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
				"Clear_Right", InNode->Value, InNode, InNode->Right, InNode->Parent);
		}
		else
		{
			std::printf(
				"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
				"InValid_Right", InNode->Value, InNode, InNode->Right, InNode->Parent);
		}

		Delete(InNode);

		return true;
	}

public:
	void Delete(Node* InNode)
	{
		InNode->Parent = nullptr;
		InNode->Left = nullptr;
		InNode->Right = nullptr;
		InNode->Value = 0;

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

public:
	bool Find(int InValue)
	{
		if (!Root || (Size == 0))
		{
			std::printf("%-15s : %s\n", "Error", "InValid Root or Size == 0.");
			return false;
		}

		// Valid Root
		Node* targetNode = Root;
		while (targetNode != nullptr)
		{
			if (InValue < targetNode->Value)
			{
				if (!targetNode->Left)
				{
					std::printf("%-15s : InValue: %-5d | Node: %-5p | LastNodeValue: %-5d | InValid Direction: %-5s\n", "Find_Failed", InValue, targetNode, targetNode->Value, "Left");
					return false;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Left;
					continue;
				}
			}
			else if (InValue > targetNode->Value)
			{
				if (!targetNode->Right)
				{
					std::printf("%-15s : InValue: %-5d | Node: %-5p | LastNodeValue: %-5d | InValid Direction: %-5s\n", "Find_Failed", InValue, targetNode, targetNode->Value, "Right");
					return false;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Right;
					continue;
				}
			}
			else // Value == targetNode->Value
			{
				std::printf("%-15s : InValue: %-5d | Node: %-5p | LastNodeValue: %-5d\n", "Find_Complete", InValue, targetNode, targetNode->Value);
				return true;
			}
		} // while

		std::printf("%-15s : %s\n", "Error", "Undefined.");
		return false;
	} // Find

public:
	Node* FindLargestInSubTree(Node* InRootNode)
	{
		if (!InRootNode)
		{
			std::printf("%-15s : %s\n", "Error", "InValid InRootNode or Size == 0.");
			return nullptr;
		}

		// Valid Root
		Node* targetNode = InRootNode;
		while (targetNode != nullptr)
		{
			if (targetNode->Right)
			{
				targetNode = targetNode->Right;
			}
			else // InValid Right Node
			{
				std::printf("%-15s : Root: %-5p | Node: %-5p | LastNodeValue: %-5d\n", "Find_Largest", InRootNode, targetNode, targetNode->Value);
				return targetNode;
			}
		}
		std::printf("%-15s : %s\n", "Error", "Undefined.");
		return nullptr;
	}

public:
	Node* FindSmallestInSubTree(Node* InRootNode)
	{
		if (!Root || (Size == 0))
		{
			std::printf("%-15s : %s\n", "Error", "InValid Root or Size == 0.");
			return nullptr;
		}

		// Valid Root
		Node* targetNode = Root;
		while (targetNode != nullptr)
		{
			if (targetNode->Left)
			{
				targetNode = targetNode->Left;
			}
			else // InValid Right Node
			{
				std::printf("%-15s : Root: %-5p | Node: %-5p | LastNodeValue: %-5d\n", "Find_Smallest", InRootNode, targetNode, targetNode->Value);
				return targetNode;
			}
		}
		std::printf("%-15s : %s\n", "Error", "Undefined.");
		return nullptr;
	}

public:
	bool Erase(int InValue)
	{
		if (!Root || (Size == 0))
		{
			std::printf("%-15s : %s\n", "Error", "InValid Root or Size == 0.");
			return false;
		}

		// Valid Root
		Node* targetNode = Root;
		while (targetNode != nullptr)
		{
			if (InValue < targetNode->Value)
			{
				if (!targetNode->Left)
				{
					std::printf("%-15s : InValue: %-5d | Node: %-5p | LastNodeValue: %-5d | InValid Direction: %-5s\n", "Erase_Failed", InValue, targetNode, targetNode->Value, "Left");
					return false;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Left;
					continue;
				}
			}
			else if (InValue > targetNode->Value)
			{
				if (!targetNode->Right)
				{
					std::printf("%-15s : InValue: %-5d | Node: %-5p | LastNodeValue: %-5d | InValid Direction: %-5s\n", "Erase_Failed", InValue, targetNode, targetNode->Value, "Right");
					return false;
				}
				else // Valid targetNode->Left
				{
					targetNode = targetNode->Right;
					continue;
				}
			}
			else // Value == targetNode->Value
			{
				// TODO
			}
		} // while

		std::printf("%-15s : %s\n", "Error", "Undefined.");
		return false;
	}
};