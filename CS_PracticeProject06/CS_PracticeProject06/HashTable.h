#pragma once

struct Node
{
	bool bExist;
	size_t HashKey;

	size_t Key; // Original Key
	int Value;

	Node* PrevNode;
	Node* NextNode;

public:
	Node()
	{
		bExist = false;
		HashKey = 0;
		Key = 0;
		Value = 0;
		PrevNode = nullptr;
		NextNode = nullptr;
	}

	~Node()
	{
		bExist = false;
		HashKey = 0;
		Key = 0;
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
	bool Insert(size_t InKey, int InValue)
	{
		// [Policy] No duplicates allowed (Set)

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Insert", "BaseBucket is invalid.");
			return false;
		}

		size_t hashkey = GetHash(InKey);

		Node* targetNodeInBucket = BaseNode + hashkey;

		/* Case01: targetNodeInBucket->bExist == false */
		if (!targetNodeInBucket->bExist)
		{
			targetNodeInBucket->bExist = true;
			targetNodeInBucket->HashKey = hashkey;

			targetNodeInBucket->Key = InKey;
			targetNodeInBucket->Value = InValue;

			++Size;

			printf("[%s/%s] %s: <%zd, %d> | %s: %zd\n", "Complete", "Insert", "Insert complete", InKey, InValue, "Size", Size);
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

			if (targetNode->Key != InKey)
			{
				continue;
			}

			if (targetNode->Value == InValue)
			{
				printf("[%s/%s] %s: <%zd, %d> | %s: %zd\n", "Failed", "Insert", "Duplicate entries are not allowed", InKey, InValue, "Size", Size);
				return false;
			}

			if (!targetNode->NextNode)
			{
				Node* newNode = new Node();

				newNode->bExist = true;
				newNode->HashKey = hashkey;

				newNode->Key = InKey;
				newNode->Value = InValue;

				newNode->PrevNode = targetNode;
				targetNode->NextNode = newNode;

				++Size;

				printf("[%s/%s] %s: <%zd, %d> | %s: %zd\n", "Complete", "Insert", "Insert complete", InKey, InValue, "Size", Size);
				return true;
			}
			else
			{
				targetNode = targetNode->NextNode;
				continue;
			}
		}

		printf("[%s/%s] %s\n", "Failed", "Insert", "Undefined.");
		return false;
	}

public:
	Node* Find(size_t InKey, int InValue)
	{
		// [Policy] No duplicates allowed

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Find", "BaseBucket is invalid.");
			return nullptr;
		}

		size_t hashkey = GetHash(InKey);

		Node* targetNodeInBucket = BaseNode + hashkey;

		/* Case01: targetNodeInBucket->bExist == false */
		if (!targetNodeInBucket->bExist)
		{
			printf("[%s/%s] %s\n", "Failed", "Find", "Invalid value in bucket.");
			return nullptr;
		}

		/* Case02: targetNodeInBucket->bExist == true */
		Node* targetNode = targetNodeInBucket;
		while (true)
		{
			if (targetNode->HashKey != hashkey)
			{
				printf("[%s/%s] %s\n", "Error", "Find", "HashKey mismatch.");
				return nullptr;
			}

			if (targetNode->Value == InValue)
			{
				printf("[%s/%s] %s\n", "Complete", "Find", "Find complete.");
				return targetNode;
			}

			if (!targetNode->NextNode)
			{
				printf("[%s/%s] %s\n", "Failed", "Find", "Invalid next node.");
				return nullptr;
			}
			else
			{
				targetNode = targetNode->NextNode;
				continue;
			}
		}

		printf("[%s/%s] %s\n", "Failed", "Find", "Undefined.");
		return nullptr;
	}

private:
	size_t GetHash(size_t InKey)
	{
		return InKey % Capacity;
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
	bool Insert(size_t InKey, int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Insert", "BaseBucket is InValid.");
			return false;
		}

		return BaseBucket->Insert(InKey, InValue);
	}

public:
	Node* Find(size_t InKey, int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Find", "BaseBucket is InValid.");
			return nullptr;
		}

		return BaseBucket->Find(InKey, InValue);
	}
};