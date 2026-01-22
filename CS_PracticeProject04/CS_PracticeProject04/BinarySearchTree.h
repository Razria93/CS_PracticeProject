#pragma once

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
};