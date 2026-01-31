#pragma once

struct Node
{
	bool bExist;

	size_t HashKey;
	int Value;

	Node* PrevNode;
	Node* NextNode;

public:
	Node()
	{
		bExist = false;
		HashKey = 0;
		Value = 0;
		PrevNode = nullptr;
		NextNode = nullptr;
	}

	~Node()
	{
		bExist = false;
		HashKey = 0;
		Value = 0;
		PrevNode = nullptr;
		NextNode = nullptr;
	}
};

struct Bucket
{
	Node* BaseNode;
	size_t Capacity;
	size_t Size;

public:
	Bucket(size_t InSize)
	{
		BaseNode = new Node[InSize];
		Capacity = InSize;
		Size = 0;
	}

	~Bucket()
	{
		delete[] BaseNode;
		Capacity = 0;
		Size = 0;
	}
};

class HashTable
{
public:
	Bucket* BaseBucket; // == std::vector<Node>(InSize) && Chainning

public:
	HashTable()
	{
		BaseBucket = nullptr;
	}

	~HashTable()
	{
		delete BaseBucket;
	}

public:
	void Initialize(size_t InSize)
	{
		if (BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Initialize", "BaseBucket is already initialized.");
			return;
		}

		BaseBucket = new Bucket(InSize);
		printf("[%s/%s] %s\n", "Complete", "Initialize", "Initialize complete.");
	}
};