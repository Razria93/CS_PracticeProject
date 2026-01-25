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
	void Clear()
	{
		Clear(Root);

		Root = nullptr;
		Size = 0;
	}

	void Clear(Node* InNode)
	{
		if (!InNode) return;

		Clear(InNode->Left);
		Clear(InNode->Right);
		Delete(InNode);
	}

public:
	void Delete(Node* InNode)
	{
		if (Node* parentNode = InNode->Parent)
		{
			if (InNode == parentNode->Left)
			{
				parentNode->Left = nullptr;
			}
			else if (InNode == parentNode->Right)
			{
				parentNode->Right = nullptr;
			}
		}
		else // bIsRoot == true
		{
			if (InNode == Root)
				Root = nullptr;
		}

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
				std::printf("%-20s : %s\n", "Error", "InValid Root. but Size != 0.");
				return false;
			}

			Root = node;
			++Size;

			std::printf("%-20s : newNode: %-5p | newValue: %-5d | Size: %-5zd\n", "Insert_Root", node, node->Value, Size);

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

					std::printf("%-20s : newNode: %-5p | newValue: %-5d | Parent: %-5p | ParentValue: %-5d | Size: %-5zd\n", "Insert_Left", node, node->Value, targetNode, targetNode->Value, Size);

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

					std::printf("%-20s : newNode: %-5p | newValue: %-5d | Parent: %-5p | ParentValue: %-5d | Size: %-5zd\n", "Insert_Right", node, node->Value, targetNode, targetNode->Value, Size);

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
				delete node;
				return false;
			}
		} // while

		std::printf("%-20s : %s\n", "Error", "Undefined.");
		return false;
	} // Insert

public:
	Node* Find(int InValue)
	{
		if (!Root)
		{
			return nullptr;
		}

		return Find(InValue, Root);
	}

	Node* Find(int InValue, Node* InNode)
	{
		if (!InNode) return nullptr;

		if (InValue == InNode->Value) return InNode;
		if (InValue < InNode->Value) return Find(InValue, InNode->Left);
		if (InValue > InNode->Value) return Find(InValue, InNode->Right);

		std::printf("%-20s : %s\n", "Error", "Undefined.");
		return nullptr;
	} // Find

public:
	Node* FindLargest()
	{
		return FindLargest(Root);
	}

	Node* FindLargest(Node* InRootNode)
	{
		if (!InRootNode) return nullptr;

		Node* largest = FindLargest(InRootNode->Right);

		return largest ? largest : InRootNode;
	}

public:
	Node* FindSmallest()
	{
		return FindSmallest(Root);
	}

	Node* FindSmallest(Node* InRootNode)
	{
		if (!InRootNode) return nullptr;

		Node* smallest = FindSmallest(InRootNode->Left);

		return smallest ? smallest : InRootNode;
	}

public:
	bool Erase(int InValue)
	{
		return Erase(InValue, Root);
	}

	bool Erase(int InValue, Node* InNode)
	{
		if (!InNode)
		{
			std::printf("%-20s : %s\n", "Error", "InValid InNode.");
			return false;
		}

		if (InValue == InNode->Value)
		{
			Node* eraseNode = InNode;
			Node* leftNode_cached = eraseNode->Left;
			Node* rightNode_cached = eraseNode->Right;

			Node* switchNode = nullptr;

			Node* largest = FindLargest(InNode->Left);
			Node* smallest = FindSmallest(InNode->Right);

			if (!largest && !smallest) return false;

			if (!largest && smallest)
				switchNode = smallest;

			if (largest && !smallest)
				switchNode = largest;

			if (largest && smallest)
			{
				if ((largest->Value - InNode->Value) >= (InNode->Value - smallest->Value))
				{
					switchNode = smallest;
				}
				else
				{
					switchNode = largest;
				}
			}

			Node* oldParentNode = switchNode->Parent ? switchNode->Parent : nullptr;
			Node* newParentNode = eraseNode->Parent ? eraseNode->Parent : nullptr;

			bool bRight = false;
			bool bLeft = false;

			if (newParentNode)
			{
				if (newParentNode->Right == eraseNode)
				{
					bRight = true;
					newParentNode->Right = nullptr;
				}
				else if (newParentNode->Left == eraseNode)
				{
					bLeft = true;
					newParentNode->Left = nullptr;
				}
			}

			Delete(eraseNode);
			eraseNode = nullptr;

			if (oldParentNode)
			{
				if (oldParentNode->Right == switchNode)
					oldParentNode->Right = nullptr;
				else if (oldParentNode->Left == switchNode)
					oldParentNode->Left = nullptr;
			}

			if (newParentNode)
			{
				if (bRight)
				{
					newParentNode->Right = switchNode;
					switchNode->Parent = newParentNode;
				}
				else if (bLeft)
				{
					newParentNode->Left = switchNode;
					switchNode->Parent = newParentNode;
				}
			}
			else
			{
				Root = switchNode;
				switchNode->Parent = nullptr;
			}

			if (leftNode_cached && (leftNode_cached != switchNode))
			{
				switchNode->Left = leftNode_cached;
				leftNode_cached->Parent = switchNode;
			}
			else
			{
				switchNode->Left = nullptr;
			}

			if (rightNode_cached && (rightNode_cached != switchNode))
			{
				switchNode->Right = rightNode_cached;
				rightNode_cached->Parent = switchNode;
			}
			else
			{
				switchNode->Right = nullptr;
			}

			--Size;

			return true;
		}

		if (InValue < InNode->Value) return Erase(InValue, InNode->Left);
		if (InValue > InNode->Value) return Erase(InValue, InNode->Right);

		std::printf("%-20s : %s\n", "Error", "Undefined.");
		return false;
	} // Erase

public:
	void TraversePreOrder()
	{
		if (!Root)
		{
			std::printf("%-20s : %s\n", "Error", "InValid Root.");
			return;
		}

		TraversePreOrder(Root);
	}

	bool TraversePreOrder(Node* InNode)
	{
		if (!InNode)
		{
			// std::printf("%-20s : %s\n", "NOTE", "InValid InNode.");
			return false;
		}

		// PreOrder
		std::printf("%-20s : NodeValue: %-11d | NodeNode: %p | ParentNode: %p | LeftNode: %p | RightNode: %p\n", "PreOrder_Cur", InNode->Value, InNode, InNode->Parent, InNode->Left, InNode->Right);

		TraversePreOrder(InNode->Left);

		TraversePreOrder(InNode->Right);

		return true;
	}

public:
	void TraverseInOrder()
	{
		if (!Root)
		{
			std::printf("%-20s : %s\n", "Error", "InValid Root.");
			return;
		}

		TraverseInOrder(Root);
	}

	bool TraverseInOrder(Node* InNode)
	{
		if (!InNode)
		{
			// std::printf("%-20s : %s\n", "NOTE", "InValid InNode.");
			return false;
		}

		TraverseInOrder(InNode->Left);

		// InOrder
		std::printf("%-20s : NodeValue: %-11d | NodeNode: %p | ParentNode: %p | LeftNode: %p | RightNode: %p\n", "InOrder_Cur", InNode->Value, InNode, InNode->Parent, InNode->Left, InNode->Right);

		TraverseInOrder(InNode->Right);

		return true;
	}

public:
	void TraversePostOrder()
	{
		if (!Root)
		{
			std::printf("%-20s : %s\n", "Error", "InValid Root.");
			return;
		}

		TraversePostOrder(Root);
	}

	bool TraversePostOrder(Node* InNode)
	{
		if (!InNode)
		{
			// std::printf("%-20s : %s\n", "NOTE", "InValid InNode.");
			return false;
		}

		TraversePostOrder(InNode->Left);

		TraversePostOrder(InNode->Right);

		// PostOrder
		std::printf("%-20s : NodeValue: %-11d | NodeNode: %p | ParentNode: %p | LeftNode: %p | RightNode: %p\n", "PostOrder_Cur", InNode->Value, InNode, InNode->Parent, InNode->Left, InNode->Right);

		return true;
	}
};