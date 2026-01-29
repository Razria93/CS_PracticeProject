#pragma once

class Stack
{
public:
	Stack()
	{
		Base = nullptr;
		Size = 0;
		Offset = 0;
	}

	~Stack()
	{
		// TODO: Clear
	}

public:
	int* Base;
	size_t Size;
	size_t Offset;
};