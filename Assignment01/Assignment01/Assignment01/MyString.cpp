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

	const char* base = s;
	size_t length = 0;

	const char* temp = nullptr;

	while (true)
	{
		temp = base + length;

		if (*temp == '\0')
		{

			printf("Find '\\0'\n");
			printf("OldBasePtr: %p | FinalSize: %zd\n", s, length);
			break;
		}
		else
		{
			++length;
			printf("Char: %c | Pointer: %p | Length: %zd\n", *temp, temp, length);
			continue;
		}
	}

	char* newBase = new char[length + 1];

	for (size_t i = 0; i < length; ++i)
	{
		newBase[i] = *(s + i);
		printf("Input: %c | Output: %c | Idx: %zd\n", *(newBase + i), *(s + i), i);
	}

	newBase[length] = '\0';
	Clear();

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

	char* newBase = new char[otherLength + 1];
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

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;
}

MyString::~MyString()
{
	printf("\n[Destructor]\n");

	printf("OldBasePtr: %p | FinalSize: %zd\n", Base, Length);

	Clear();

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

	const char* base = s;
	size_t length = 0;

	const char* temp = nullptr;

	while (true)
	{
		temp = base + length;

		if (*temp == '\0')
		{

			printf("Find '\\0'\n");
			printf("OldBasePtr: %p | FinalSize: %zd\n", s, length);
			break;
		}
		else
		{
			++length;
			printf("Char: %c | Pointer: %p | Length: %zd\n", *temp, temp, length);
			continue;
		}
	}

	char* newBase = new char[Length + length + 1];
	size_t newLength = Length + length;

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < length; ++j)
	{

		newBase[Length + j] = *(s + j);
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;
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

	char* newBase = new char[Length + otherLength + 1];
	size_t newLength = Length + otherLength;

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < otherLength; ++j)
	{

		newBase[Length + j] = other.Base[j];
	}

	newBase[newLength] = '\0';

	MyString newString;
	newString.Base = newBase;
	newString.Length = newLength;
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
	printf("\n[LastIndexOf]\n");

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
	bool bEqualStart_cached = false;
	bool bEqualEnd_cached = false;

	size_t startIdx = 0;
	size_t endIdx = 0;
	size_t startIdx_cached = 0;
	size_t endIdx_cached = 0;

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
						bEqualStart_cached = true;
						bEqualEnd_cached = true;

						startIdx_cached = i + j;
						endIdx_cached = i + j;

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

					bEqualStart_cached = bEqualStart;
					bEqualEnd_cached = bEqualEnd;
					startIdx_cached = startIdx;
					endIdx_cached = endIdx;

					bEqualStart = false;
					bEqualEnd = false;
					startIdx = 0;
					endIdx = 0;

					continue;
				}
			}
			else
			{
				bEqualStart = false;
				bEqualEnd = false;
				startIdx = 0;
				endIdx = 0;

				continue;
			}
		} // for j
	} // for i

	if (bEqualStart_cached == true && bEqualEnd_cached == true)
	{
		printf("Valid equal string[startIdx: %zd | endIdx: %zd]\n", startIdx_cached, endIdx_cached);
		return (int)startIdx_cached;
	}

	printf("InValid equal string\n");
	return -1;
}

void MyString::Interleave(const char* s)
{
	printf("\n[Interleave]\n");

	const char* temp = s;

	const char* base = s;
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

	char* newBase = new char[Length + length + 1];
	size_t newLength = Length + length;

	bool bIsLarge = (int)(Length - length) > 0 ? true : false;
	size_t lengthSubtract = bIsLarge ? (Length - length) : (length - Length);

	for (size_t i = 0; i < newLength - lengthSubtract; ++i)
	{
		bool shift = (i % 2 != 0) ? true : false;
		size_t idx = i / 2;

		if (shift == false)
		{
			newBase[i] = Base[idx];
		}
		else // shift == true
		{
			newBase[i] = *(s + idx);
		}
	}

	if (lengthSubtract != 0 && bIsLarge == true)
	{
		for (size_t j = 0; j < lengthSubtract; ++j)
		{
			newBase[(newLength - lengthSubtract) + j] = Base[(Length - lengthSubtract) + j];
		}
	}
	else if (lengthSubtract != 0 && bIsLarge == false)
	{
		for (size_t k = 0; k < lengthSubtract; ++k)
		{
			newBase[(newLength - lengthSubtract) + k] = base[(length - lengthSubtract) + k];
		}
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;
	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);
}

bool MyString::RemoveAt(unsigned int index)
{
	printf("\n[RemoveAt]\n");

	if (index >= Length)
	{
		printf("Index out of range\n");
		printf("InIndex: %d | Length: %zd\n", index, Length);
		return false;
	}

	printf("InIdex: %d | Target: %c\n", index, Base[index]);

	char* newBase = new char[Length];
	size_t newLength = Length - 1;

	for (size_t i = 0; i < newLength; ++i)
	{
		if (i < index)
		{
			newBase[i] = Base[i];
		}
		else // i >= index
		{
			newBase[i] = Base[i + 1];
		}
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);

	return false;
}

void MyString::PadLeft(unsigned int totalLength)
{
	printf("\n[PadLeft]\n");

	if (totalLength <= Length)
	{
		printf("Specified TotalLength is too small for padding\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	char* newBase = new char[totalLength + 1];
	size_t newLength = totalLength;
	size_t lengthSubtract = totalLength - Length;

	for (size_t i = 0; i < lengthSubtract; ++i)
	{
		newBase[i] = ' ';
	}

	for (size_t j = 0; j < Length; ++j)
	{
		newBase[lengthSubtract + j] = Base[j];
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);

	return;
}

void MyString::PadLeft(unsigned int totalLength, const char c)
{
	printf("\n[PadLeft(with %c)]\n", c);

	if (totalLength <= Length)
	{
		printf("Specified TotalLength is too small for padding\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	if (c == '\0')
	{
		printf("Null character('\\0) cannot be used for padding.\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	char* newBase = new char[totalLength + 1];
	size_t newLength = totalLength;
	size_t lengthSubtract = totalLength - Length;

	for (size_t i = 0; i < lengthSubtract; ++i)
	{
		newBase[i] = c;
	}

	for (size_t j = 0; j < Length; ++j)
	{
		newBase[lengthSubtract + j] = Base[j];
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);

	return;
}

void MyString::PadRight(unsigned int totalLength)
{
	printf("\n[PadRight]\n");

	if (totalLength <= Length)
	{
		printf("Specified TotalLength is too small for padding\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	char* newBase = new char[totalLength + 1];
	size_t newLength = totalLength;
	size_t lengthSubtract = totalLength - Length;

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < lengthSubtract; ++j)
	{
		newBase[Length + j] = ' ';
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);

	return;
}

void MyString::PadRight(unsigned int totalLength, const char c)
{
	printf("\n[PadRight(with %c)]\n", c);

	if (totalLength <= Length)
	{
		printf("Specified TotalLength is too small for padding\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	if (c == '\0')
	{
		printf("Null character('\\0) cannot be used for padding.\n");
		printf("InTotalLength: %d | StringLength: %zd\n", totalLength, Length);
		return;
	}

	char* newBase = new char[totalLength + 1];
	size_t newLength = totalLength;
	size_t lengthSubtract = totalLength - Length;

	for (size_t i = 0; i < Length; ++i)
	{
		newBase[i] = Base[i];
	}

	for (size_t j = 0; j < lengthSubtract; ++j)
	{
		newBase[Length + j] = c;
	}

	newBase[newLength] = '\0';
	Clear();

	Base = newBase;
	Length = newLength;

	printf("NewBasePtr: %p | FinalSize: %zd\n", Base, Length);

	return;
}

void MyString::Reverse()
{
	printf("\n[Reverse]\n");

	if (Length <= 1)
	{
		printf("String length is too short to reverse.\n");
		printf("Length: %zd\n", Length);
	}

	for (size_t i = 0; i < (Length / 2); ++i)
	{
		printf("[Change] idx: %zd (%c) | idx: %zd (%c)\n", i, Base[i], (Length - 1) - i, Base[(Length - 1) - i]);

		const char temp = Base[i];
		Base[i] = Base[(Length - 1) - i];
		Base[(Length - 1) - i] = temp;
	}
}

bool MyString::operator==(const MyString& rhs) const
{
	printf("\n[operator== Override]\n");

	if (Length != rhs.Length)
	{
		printf("Length is not Equal\n");
		printf("Length: %zd | rhs.Length: %zd\n", Length, rhs.Length);
		return false;
	}

	bool bEqual = false;

	for (size_t i = 0; i < Length; ++i)
	{
		if (Base[i] != rhs.Base[i])
		{
			printf("Base is not Equal\n");
			printf("Base[%zd]: %c | rhs[%zd]: %c\n", i, Base[i], i, rhs.Base[i]);

			bEqual = false;
			return false;
		}
		else // Base[i] == rhs.Base[i]
		{
			bEqual = true;
		}
	}

	return bEqual;
}

void MyString::ToLower()
{
	int a = (int)'a'; // 97
	int z = (int)'z';
	int A = (int)'A'; // 65
	int Z = (int)'Z';

	int subtract = a - A;

	printf("a: %d | A: %d | subtract: %d\n", a, A, subtract);
	printf("z: %d | Z: %d | subtract: %d\n", z, Z, subtract);

	for (int i = 0; i < Length; ++i)
	{
		char temp = Base[i];
		printf("%c: %d\n", temp, (int)temp);

		if (temp >= A && temp <= Z)
		{
			int temp_int = (int)Base[i] + subtract;
			Base[i] = (char)temp_int;
			printf("Before: %d(%c) | After: %d(%c)\n", (int)temp, temp, temp_int, (char)temp_int);
		}
	}
}

void MyString::ToUpper()
{
	int a = (int)'a'; // 97
	int z = (int)'z'; 
	int A = (int)'A'; // 65
	int Z = (int)'Z';
	
	int subtract = a - A;

	printf("a: %d | A: %d | subtract: %d\n", a, A, subtract);
	printf("z: %d | Z: %d | subtract: %d\n", z, Z, subtract);

	for (int i = 0; i < Length; ++i)
	{
		char temp = Base[i];
		printf("%c: %d\n", temp, (int)temp);

		if (temp >= a && temp <= z)
		{
			int temp_int = (int)Base[i] - subtract;
			Base[i] = (char)temp_int;
			printf("Before: %d(%c) | After: %d(%c)\n", (int)temp, temp, temp_int, (char)temp_int);
		}
	}
}

void MyString::Clear()
{
	delete[] Base;
	Base = nullptr;
	Length = 0;
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
			printf("'\\0' is Found in target MyString and early return\n");
			break;
		}

		printf("%c", newChar);
	}

	printf("\n");
}

} // namespace assignment1
