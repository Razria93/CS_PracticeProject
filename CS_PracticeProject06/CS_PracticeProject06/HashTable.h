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

public:
	bool Insert(int InValue)
	{
		// [Policy] No duplicates allowed (Set)

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Insert", "BaseBucket is invalid.");
			return false;
		}

		size_t key = static_cast<size_t>(InValue);
		size_t hashkey = HashFunction(key);

		Node* targetNodeInBucket = BaseNode + hashkey;

		/* Case01: targetNodeInBucket->bExist == false */
		if (!targetNodeInBucket->bExist)
		{
			targetNodeInBucket->bExist = true;
			targetNodeInBucket->HashKey = hashkey;
			targetNodeInBucket->Value = InValue;

			++Size;

			printf("[%s/%s] %s: %d | %s: %zd\n", "Complete", "Insert", "Insert complete", InValue, "Size", Size);
			return true;
		}

		/* Case02: targetNodeInBucket->bExist == true */
		Node* targetNode = targetNodeInBucket;
		while (true)
		{
			if (targetNode->HashKey != hashkey)
			{
				printf("[%s/%s] %s\n", "Error", "Insert", "HashKey mismatch.");
				return false;
			}

			if (targetNode->Value == InValue)
			{
				printf("[%s/%s] %s\n", "Failed", "Insert", "Duplicate entries are not allowed.");
				return false;
			}

			if (!targetNode->NextNode)
			{
				Node* newNode = new Node();

				newNode->bExist = true;
				newNode->HashKey = hashkey;
				newNode->Value = InValue;

				newNode->PrevNode = targetNode;
				targetNode->NextNode = newNode;

				++Size;

				printf("[%s/%s] %s: %d | %s: %zd\n", "Complete", "Insert", "Insert complete", InValue, "Size", Size);
				return true;
			}
			else
			{
				targetNode = targetNode->NextNode;
				continue;
			}
		}

		printf("[%s/%s] %s\n", "Failed", "Insert", "Undefined");
		return false;
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

public:
	bool Insert(int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Insert", "BaseBucket is InValid.");
			return false;
		}

		return BaseBucket->Insert(InValue);
	}
};