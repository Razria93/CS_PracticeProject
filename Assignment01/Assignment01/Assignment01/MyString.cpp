#include "MyString.h"
#include <cstdio>

namespace assignment1
{

MyString::MyString()
{
	Base = nullptr;
	Length = 0;
}

MyString::MyString(const char* s)
{
	printf("\n[Default-Constructor]\n");

	const char* temp = s;
	size_t length = 0;

	while (true)
	{
		temp = s + length;

		if (*temp == '\0')
		{

			printf("Find '\\0'\n");
			printf("OldBasePtr: %p | FinalSize: %zd\n", s, length);
			break;
		}
		else
		{
			++length;
			printf("char: %c | pointer: %p | length: %zd\n", *temp, temp, length);
			continue;
		}
	}

	char* newBase = new char[length];

	for (size_t i = 0; i < length; ++i)
	{
		newBase[i] = *(s + i);
		printf("Input: %c | Output: %c | idx: %zd\n", *(newBase + i), *(s + i), i);
	}

	Base = newBase;
	Length = length;
	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);
}

MyString::MyString(const MyString& other)
{
	printf("\n[Copy-Constructor]\n");

	const char* otherBase = other.Base;
	size_t otherLength = other.Length;

	if (!otherBase)
	{
		printf("Base pointer is nullptr\n");
		return;
	}

	char* newBase = new char[otherLength];
	size_t newLength = otherLength;

	for (int i = 0; i < otherLength; ++i)
	{
		char newChar = *(otherBase + i);

		if (newChar == '\0')
		{
			newLength = i;
			printf("'\\0' is Valid in other MyString and early return\n");
			break;
		}

		newBase[i] = newChar;
	}

	Base = newBase;
	Length = newLength;
}

MyString::~MyString()
{
	printf("\n[Destructor]\n");

	printf("OldBasePtr: %p | FinalSize: %zd\n", Base, Length);

	delete[] Base;
	Base = nullptr;
	Length = 0;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);
}

unsigned int MyString::GetLength() const
{
	return (int)Length;
}

const char* MyString::GetCString() const
{
	return Base;
}

void MyString::Append(const char* s)
{
	printf("\n[Append]\n");

	const char* temp = s;
	size_t length = 0;

	while (true)
	{
		temp = s + length;

		if (*temp == '\0')
		{

			printf("Find '\\0'\n");
			printf("OldBasePtr: %p | FinalSize: %zd\n", s, length);
			break;
		}
		else
		{
			++length;
			printf("char: %c | pointer: %p | length: %zd\n", *temp, temp, length);
			continue;
		}
	}

	char* newBase = new char[Length + length];

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < length; ++j)
	{

		newBase[Length + j] = *(s + j);
	}

	Base = newBase;
	Length = Length + length;
	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);
}

MyString MyString::operator+(const MyString& other) const
{
	printf("\n[operator+ Override]\n");

	const char* otherBase = other.Base;
	size_t otherLength = other.Length;

	if (!otherBase)
	{
		printf("Base pointer is nullptr\n");
		return MyString();
	}

	char* newBase = new char[Length + otherLength];

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < otherLength; ++j)
	{

		newBase[Length + j] = other.Base[j];
	}

	MyString newString;
	newString.Base = newBase;
	newString.Length = Length + otherLength;
	// newString.Print();

	return newString;
}

int MyString::IndexOf(const char* s)
{
	printf("\n[IndexOf]\n");

	const char* base = s;
	size_t length = 0;

	const char* temp = nullptr;

	while (true)
	{
		temp = base + length;

		if (*temp == '\0')
		{

			printf("Find '\\0'\n");
			printf("InBasePtr: %p | FinalSize: %zd\n", s, length);
			break;
		}
		else
		{
			++length;
			printf("char: %c | pointer: %p | length: %zd\n", *temp, temp, length);
			continue;
		}
	}

	bool bEqualStart = false;
	bool bEqualEnd = false;

	size_t startIdx = 0;
	size_t endIdx = 0;

	for (size_t i = 0; i < Length; ++i)
	{
		for (size_t j = 0; j < length; ++j)
		{
			if (Base[i + j] == base[j])
			{
				if (bEqualStart == false)
				{
					if (length == 1)
					{
						startIdx = i + j;
						endIdx = i + j;

						bEqualStart = true;
						bEqualEnd = true;

						break;
					}
					else
					{
						startIdx = i + j;
						bEqualStart = true;

						continue;
					}
				}
				else if (bEqualEnd == false && j == (length - 1))
				{
					endIdx = i + j;
					bEqualEnd = true;

					break;
				}
			}
			else
			{
				bEqualStart = false;
				bEqualEnd = false;
				startIdx = 0;
				endIdx = 0;

				break;
			}
		} // for j

		if (bEqualStart == true && bEqualEnd == true) // Early-Return
		{
			printf("Valid equal string[startIdx: %zd | endIdx: %zd]\n", startIdx, endIdx);
			return (int)startIdx;
		}
			} // for i

	printf("InValid equal string\n");
	return -1;
}

int MyString::LastIndexOf(const char* s)
{
	return 0;
}

void MyString::Interleave(const char* s)
{
}

bool MyString::RemoveAt(unsigned int index)
{
	return false;
}

void MyString::PadLeft(unsigned int totalLength)
{
}

void MyString::PadLeft(unsigned int totalLength, const char c)
{
}

void MyString::PadRight(unsigned int totalLength)
{
}

void MyString::PadRight(unsigned int totalLength, const char c)
{
}

void MyString::Reverse()
{
}

bool MyString::operator==(const MyString& rhs) const
{
	return false;
}

void MyString::ToLower()
{
}

void MyString::ToUpper()
{
}

void MyString::Print()
{
	printf("\n[Print]\n");

	if (!Base)
	{
		printf("Base pointer is nullptr\n");
		return;
	}

	for (int i = 0; i < Length; ++i)
	{
		char newChar = *(Base + i);

		if (newChar == '\0')
		{
			printf("'\\0' is Valid in target MyString and early return\n");
			break;
		}

		printf("%c", newChar);
	}

	printf("\n");
}

} // namespace assignment1
