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

	stack->Pop();
	stack->Pop();
	stack->Pop();

	delete stack;
	
	return 0;
}