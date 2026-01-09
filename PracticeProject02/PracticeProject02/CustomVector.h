#pragma once

#include <iostream>
#include <bitset>

template<typename T> // Determined at compile time
class CustomVector
{
private:
	T* Data;
	size_t Capacity;
	size_t Size;

public:
	CustomVector()
	{
		std::printf("[Constructor]\n");

		Data = nullptr;
		Capacity = 0;
		Size = 0;
	}

	~CustomVector()
	{
		delete[] Data;
		Data = nullptr;
	}

	CustomVector(const CustomVector&) = delete;				// copy constructor				[deprecated]
	CustomVector& operator=(const CustomVector&) = delete;	// copy assignment operator		[deprecated]

public:
	size_t capacity() const { return Capacity; }
	size_t size() const { return Size; }

public:
	T* begin() { return Data; }
	T* end() { return Data + Size; }
	const T* begin() const { return Data; }
	const T* end()   const { return Data + Size; }

public:
	bool empty() const { return Size == 0; }

public:
	void push_back(T InData)
	{
		std::printf("[push_back]\n");

		// -----------------------------------------------------------------------------------------------
		// [TODO] Refactor
		// 1. 'new T[n]' allocates memory AND calls default constructors for all 'n' elements.
		// 2. 'malloc' (or allocator) only reserves raw memory without any initialization.
		// 3. Vector uses 'placement new' to construct objects only when they are actually needed.
		// -----------------------------------------------------------------------------------------------

		// Reallocate to increase capacity
		if (Size >= Capacity)
		{
			size_t newCapacity = (Capacity == 0) ? 1 : Capacity * 2;
			if (newCapacity < Capacity) return; // overflow guard

			T* tempData = new T[newCapacity];

			for (size_t i = 0; i < Size; ++i)
			{
				tempData[i] = Data[i];
			}

			delete[] Data;
			Data = tempData;
			Capacity = newCapacity;
		}

		Data[Size] = InData;
		++Size;

		PrintData();
	}

	void insert(size_t InIndex, const T& InData)
	{
		std::printf("[insert] ElementNum: %zu\n", InIndex);

		// Check Area [0, Size]
		if (InIndex > Size) return;

		// Push_Back
		if (InIndex == Size)
		{
			push_back(InData);
			return;
		}

		// Insert
		if (Size == Capacity)
		{
			size_t newCapacity = (Capacity == 0) ? 1 : Capacity * 2;
			if (newCapacity < Capacity) return; // overflow guard

			T* tempData = new T[newCapacity];

			// Copy Element_Forward
			for (size_t i = 0; i < InIndex; i++)
			{
				tempData[i] = Data[i];
			}

			// Insert Element_InData
			tempData[InIndex] = InData;

			// Copy Element_Backward
			for (size_t i = InIndex; i < Size; i++)
			{
				tempData[i + 1] = Data[i];
			}

			delete[] Data;

			Data = tempData;
			Capacity = newCapacity;
			++Size;
		}
		else // (Size < Capacity)
		{
			// Move Backward-Elements
			for (size_t i = Size; i > InIndex; i--)
			{
				Data[i] = Data[i - 1];
			}

			Data[InIndex] = InData;
			++Size;
		}

		PrintData();
	}

	void erase(size_t InIndex)
	{
		std::printf("[erase] ElementNum: %zu\n", InIndex);

		// Check Area [0, Size]
		if (InIndex >= Size) return;

		// Push_Back
		if (InIndex == Size - 1)
		{
			pop_back();
			return;
		}

		// Copy Element_Backward
		for (size_t i = InIndex; i < Size - 1; i++)
		{
			Data[i] = Data[i + 1];
		}

		--Size;

		PrintData();
	}

	void pop_back()
	{
		std::printf("[pop_back]\n");

		if (Size == 0) return;

		--Size;

		PrintData();
	}

	void clear()
	{
		std::printf("[clear]\n");

		if (Size == 0) return;

		Size = 0;

		PrintData();
	}

	// Print Function
public:
	void PrintData() const
	{
		std::printf("==============================\n");

		if (Data)
		{
			std::printf("%-15s : %p\n", "Data", (void*)Data);
		}
		else
			std::printf("%-15s : %p\n", "Data", nullptr);

		{
			std::printf("%-15s : %s\n", "Type", typeid(T).name());
			std::printf("%-15s : %zu\n", "ElementSize", sizeof(T));
			std::printf("%-15s : %zu\n", "Capacity", Capacity);
			std::printf("%-15s : %zu\n", "Size", Size);
		}

		std::printf("==============================\n");
	}

	void PrintElements() const
	{
		std::printf("[PrintElements]\n");

		if (Size == 0) return;

		std::printf("==============================\n");

		for (size_t i = 0; i < Size; i++)
		{
			std::cout << "Element_" << i << ": " << Data[i] << std::endl;
		}

		std::printf("==============================\n");
	}
};

template<>
class CustomVector<bool>
{
private:
	uint8_t* Data;		// bit container
	size_t Capacity;	// in bits
	size_t Size;		// in bits

public:
	CustomVector()
	{
		std::printf("[Constructor<bool>]\n");

		Data = nullptr;
		Capacity = 0;		// capacity in bits (number of bool elements that can be stored) 
		Size = 0;			// size in bits (number of bool elements currently stored)
	}

	~CustomVector()
	{
		delete[] Data;
		Data = nullptr;
		Capacity = 0;
		Size = 0;
	}

	CustomVector(const CustomVector&) = delete;				// copy constructor				[deprecated]
	CustomVector& operator=(const CustomVector&) = delete;	// copy assignment operator		[deprecated]

public:
	size_t capacityBits() const { return Capacity; }
	size_t sizeBits() const { return Size; }
	bool empty() const { return Size == 0; }

public:
	bool operator[](size_t InIndex) const	// Read-Only (TODO: BitRef)
	{
		if (InIndex >= Size) return false;

		return GetBit(InIndex);
	}

public:
	void push_back(bool InData)
	{
		std::printf("[push_back<bool>]\n");

		if (!EnsureCapacity(Size + 1)) return;

		SetBit(Size, InData);
		++Size;

		PrintData();
	}

	void pop_back()
	{
		std::printf("[pop_back<bool>]\n");

		if (Size == 0) return;


		SetBit(Size - 1, false);
		--Size;

		PrintData();
	}

	void clear()
	{
		std::printf("[clear<bool>]\n");

		Size = 0;

		PrintData();
	}

	void insert(size_t InIndex, bool InData)
	{
		std::printf("[insert<bool>] ElementNum: %zu\n", InIndex);

		// Check Area [0, Size]
		if (InIndex > Size) return;

		// Ensure Capacity
		if (!EnsureCapacity(Size + 1)) return;

		// shift right (bit-wise)
		for (size_t i = Size; i > InIndex; --i)
		{
			// Shift: Data[i - 1] -> Data[i]
			SetBit(i, GetBit(i - 1));
		}

		SetBit(InIndex, InData);
		++Size;

		PrintData();
	}

	void erase(size_t InIndex)
	{
		std::printf("[erase<bool>] ElementNum: %zu\n", InIndex);

		// Check Area [0, Size]
		if (InIndex >= Size) return;

		// Push_Back
		if (InIndex == Size - 1)
		{
			pop_back();
			return;
		}

		// shift left (bit-wise)
		for (size_t i = InIndex; i < Size - 1; ++i)
		{
			// Shift: Data[i] <- Data[i + 1]
			SetBit(i, GetBit(i + 1));
		}

		SetBit(Size - 1, false);
		--Size;

		PrintData();
	}

private:
	// [Set] bitIndex가 속한 바이트에서 마스크 비트만 갱신한다(OR로 켬, ~mask AND로 끔). 다른 비트는 보존한다.
	// [Set] Update only the masked bit in the owning byte (OR to set, AND with ~mask to clear); preserve all other bits.
	void SetBit(size_t InIndex, bool Value)
	{
		const size_t byteIndex = Calculate_ByteIndex(InIndex);
		const uint8_t bitMask = Calculate_BitMask(InIndex);

		if (Value == true)	Data[byteIndex] |= bitMask;
		else				Data[byteIndex] &= uint8_t(~bitMask);
	}

	// [Get] bitIndex가 속한 바이트를 찾고, 싱글 비트 마스크로 해당 비트가 켜져있는지(1인지) 확인한다
	// [Get] Find the owning byte for InBitIndex and use a single-bit mask to test whether that bit is set.
	bool GetBit(size_t InIndex) const
	{
		const size_t byteIndex = Calculate_ByteIndex(InIndex);
		const uint8_t bitMask = Calculate_BitMask(InIndex);

		return (Data[byteIndex] & bitMask) != 0 ? true : false;
	}

private:
	// Map 'bit index' -> 'byte slot + single-bit mask(only that bit is 1)'.
	// ex) InBitIndex=10 -> byteIndex=1, mask=0b00000100
	static size_t Calculate_ByteSize(size_t Inbit) { return (Inbit + 7) / 8; }						// 'bit -> Byte': [Inbit == 0]: 0byte / [Inbit == 1 ~ 8]: 1byte / [Inbit == 9 ~ 16]: 2byte ...
	static size_t Calculate_ByteIndex(size_t InbitIndex) { return (InbitIndex / 8); }
	static uint8_t Calculate_BitMask(size_t InbitIndex) { return uint8_t(1u << (InbitIndex % 8)); }	// Build BitMask Function / 1u == unsigned int Type `1`

private:
	bool EnsureCapacity(size_t InRequireBitCapacity)
	{
		if (InRequireBitCapacity <= Capacity) return true;

		size_t newCapacity = (Capacity == 0) ? 1 : Capacity;
		while (newCapacity < InRequireBitCapacity)
		{
			size_t oldCapacity = newCapacity;
			newCapacity *= 2;								// 2x increase
			if (newCapacity < oldCapacity) return false;	// Check Overflow
		}

		const size_t oldByteSize = Calculate_ByteSize(Capacity);
		const size_t newByteSize = Calculate_ByteSize(newCapacity);

		if (newByteSize == oldByteSize)
		{
			Capacity = newCapacity; // Update logical capacity Only
			return true;
		}

		// uint8_t* temp = new (std::nothrow) uint8_t[newBytes]();
		uint8_t* tempData = new uint8_t[newByteSize]();

		if (!tempData) return false;

		if ((Data != nullptr) && (oldByteSize > 0))
		{
			for (size_t i = 0; i < oldByteSize; ++i)
			{
				tempData[i] = Data[i]; // Copy from `Data` Vector to `TempData` Vector
			}
		}

		delete[] Data;

		Data = tempData;
		Capacity = newCapacity;

		return true;
	}

public:
	void PrintData() const
	{
		std::printf("==============================\n");

		std::printf("%-15s : %p\n", "Data", (void*)Data);
		std::printf("%-15s : %s\n", "Type", typeid(bool).name());
		std::printf("%-15s : %zu\n", "ElementSize", sizeof(bool));
		std::printf("%-15s : %zu\n", "Capacity(bits)", Capacity);
		std::printf("%-15s : %zu\n", "Size(bits)", Size);
		std::printf("%-15s : %zu\n", "Capacity(bytes)", Calculate_ByteSize(Capacity));
		std::printf("%-15s : %zu\n", "Size(bytes)", Calculate_ByteSize(Size));

		std::printf("==============================\n");
	}

	void PrintElements() const
	{
		std::printf("[PrintElements<bool>]\n");
		if (Size == 0) return;

		std::printf("==============================\n");
		for (size_t i = 0; i < Size; ++i)
		{
			std::cout << "Element_" << i << ": " << (GetBit(i) ? 1 : 0) << "\n";
		}
		std::printf("==============================\n");
	}

public:
	void PrintBitLayout(size_t InBitIndex) const
	{
		std::printf("[PrintBitLayout]\n");

		if (!Data)
		{
			std::printf("Data is null\n");
			return;
		}

		if (InBitIndex >= Capacity)
		{
			std::printf("Out of range: InBitIndex=%zu | Capacity(Bit) = %zu\n", InBitIndex, Capacity);
			return;
		}

		const size_t byteIndex = Calculate_ByteIndex(InBitIndex);
		const size_t bitOffset = InBitIndex % 8;
		const uint8_t bitMask = Calculate_BitMask(InBitIndex);

		const uint8_t byteValue = Data[byteIndex];
		const uint8_t masked = uint8_t(byteValue & bitMask);
		const bool bitValue = (masked != 0);

		const std::string maskBits = std::bitset<8>(bitMask).to_string();
		const std::string byteBits = std::bitset<8>(byteValue).to_string();
		const std::string andBits = std::bitset<8>(masked).to_string();

		std::printf("==============================\n");

		std::printf("%-15s : %zu\n", "InBitIndex", InBitIndex);
		std::printf("%-15s : %zu\n", "ByteIndex", byteIndex);
		std::printf("%-15s : %zu\n", "BitOffset", bitOffset);

		std::printf("%-15s : %s\n", "Mask", maskBits.c_str());
		std::printf("%-15s : %s\n", "ByteValue", byteBits.c_str());
		std::printf("%-15s : %s\n", "Byte&Mask", andBits.c_str());

		std::printf("%-15s : %d\n", "BitValue", bitValue ? 1 : 0);

		char marker[9] = "........";
		marker[7 - bitOffset] = '^';
		std::printf("%-15s : %s\n", "Marker", marker);

		std::printf("==============================\n");
	}
};
