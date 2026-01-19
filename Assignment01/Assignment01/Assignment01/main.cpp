#include "MyString.h"
#include <cstdio>

using namespace assignment1;

int main()
{
	MyString str01("Hello");
	str01.Print();

	printf("\n[Get]\n");
	const char* getBase = str01.GetCString();
	size_t getLength = str01.GetLength();
	printf("getBase: %p | getLength: %zd\n", getBase, getLength);

	MyString str02(str01);
	str02.Print();

	str02.Append(" World!");
	str02.Print();

	return 0;
} // Call Destructor