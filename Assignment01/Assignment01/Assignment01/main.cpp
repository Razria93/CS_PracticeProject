#include "MyString.h"
#include <cstdio>

using namespace assignment1;

int main()
{
	MyString str01("Hello");
	const char* getBase = str01.GetCString();
	size_t getLength = str01.GetLength();
	printf("getBase: %p | getLength: %zd\n", getBase, getLength);
	str01.Print();
	return 0;
} // Call Destructor