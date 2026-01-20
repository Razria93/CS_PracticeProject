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
	printf("GetBase: %p | GetLength: %zd\n", getBase, getLength);

	MyString str02(str01);
	str02.Print();

	str02.Append(" World!");
	str02.Print();

	// [Why the Copy Constructor and Destructor are Invoked]
	// 1. Temporary object creation: Result of 'str01 + str02'
	// 2. Copy construction: 'str03' initialized from the temporary object
	// 3. Destruction: Temporary object destroyed at the semicolon (;)
	MyString str03 = str01 + str02;
	printf("str03: %p\n", &str03);
	str03.Print();

	int idx00 = str03.IndexOf("str");
	printf("IndexOf: %d\n", idx00);
	int idx01 = str03.IndexOf("llo");
	printf("IndexOf: %d\n", idx01);
	int idx02 = str03.IndexOf("!");
	printf("IndexOf: %d\n", idx02);

	int idx03 = str03.LastIndexOf("str");
	printf("IndexOf: %d\n", idx03);
	int idx04 = str03.LastIndexOf("llo");
	printf("IndexOf: %d\n", idx04);
	int idx05 = str03.LastIndexOf("!");
	printf("IndexOf: %d\n", idx05);

	MyString str04("Shift");
	str04.Interleave("Change");
	str04.Print();

	str04.RemoveAt(10);
	str04.Print();
	str04.RemoveAt(10);
	str04.Print();

	return 0;
} // Call Destructor