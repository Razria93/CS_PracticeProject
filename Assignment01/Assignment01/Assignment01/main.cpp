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

	MyString str05("PadLeft_1");
	str05.PadLeft(10);
	str05.Print();

	MyString str06("PadLeft_2");
	str06.PadLeft(10, '\0');
	str06.Print();

	MyString str07("PadLeft_3");
	str07.PadLeft(10, '#');
	str07.Print();

	MyString str08("PadRight_1");
	str08.PadRight(15);
	str08.Print();

	MyString str09("PadRight_2");
	str09.PadRight(15, '\0');
	str09.Print();

	MyString str10("PadRight_3");
	str10.PadRight(15, '#');
	str10.Print();

	MyString str11("Reverse");
	str11.Reverse();
	str11.Print();

	MyString str12("Change");
	str12.Reverse();
	str12.Print();

	MyString str13("1");
	str13.Reverse();
	str13.Print();

	MyString str14("Change");
	MyString str15("Change");
	printf("str11 and str12 is equal? : %s", (str14 == str15) ? "true" : "false\n"); // true

	str14.Reverse();
	printf("str11 and str12 is equal? : %s", (str14 == str15) ? "true" : "false\n"); // false

	MyString str16("LoWer");

	printf("\n[Before]");
	str16.Print();

	str16.ToLower();

	printf("\n[After]");
	str16.Print();

	return 0;
} // Call Destructor