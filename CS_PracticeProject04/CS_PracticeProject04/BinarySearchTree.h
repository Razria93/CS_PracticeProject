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