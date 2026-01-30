#include <iostream>
#include "Stack.h"

int main()
{
	Stack* stack = new Stack;

	stack->Push(0);
	stack->Push(1);
	stack->Push(2);
	stack->Push(3);
	stack->Push(4);

	printf("[%s]%-20s: %zd\n", "main", "Size", stack->GetSize());
	printf("[%s]%-20s: %s\n", "main", "IsEmpty", stack->IsEmpty() ? "True" : "False");

	stack->Pop();
	stack->Pop();
	stack->Pop();

	int outValue = 0;
	if (stack->Peek(outValue))
	{
		printf("[%s]%-20s: %d\n", "main", "PeekValue", outValue);
	}
	else
	{
		printf("[%s]%-20s: %s\n", "main", "PeekValue", "Failed");
	}

	delete stack;
	
	return 0;
}