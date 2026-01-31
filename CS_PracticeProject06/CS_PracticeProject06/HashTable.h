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

			if (targetNode->Key == InKey && targetNode->Value == InValue)
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
	bool Remove(size_t InKey, int InValue)
	{
		// [Policy] No duplicates allowed

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Remove", "BaseBucket is invalid.");
			return false;
		}

		size_t hashkey = GetHash(InKey);

		Node* targetNodeInBucket = BaseNode + hashkey;

		/* Case01: targetNodeInBucket->bExist == false */
		if (!targetNodeInBucket->bExist)
		{
			printf("[%s/%s] %s\n", "Failed", "Remove", "Invalid value in bucket.");
			return false;
		}

		/* Case02: targetNodeInBucket->bExist == true */
		Node* targetNode = targetNodeInBucket;
		while (true)
		{
			if (targetNode->HashKey != hashkey)
			{
				printf("[%s/%s] %s\n", "Error", "Remove", "HashKey mismatch.");
				return false;
			}

			if (targetNode->Key == InKey && targetNode->Value == InValue)
			{
				DeleteNode(targetNode);

				printf("[%s/%s] %s\n", "Complete", "Remove", "Remove complete.");
				return true;
			}

			if (!targetNode->NextNode)
			{
				printf("[%s/%s] %s\n", "Failed", "Remove", "Invalid next node.");
				return false;
			}
			else
			{
				targetNode = targetNode->NextNode;
				continue;
			}
		}

		printf("[%s/%s] %s\n", "Failed", "Remove", "Undefined.");
		return false;
	}

public:
	bool Contain(size_t InKey)
	{
		// [Policy] No duplicates allowed

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Contain", "BaseBucket is invalid.");
			return false;
		}

		size_t hashkey = GetHash(InKey);

		Node* targetNodeInBucket = BaseNode + hashkey;

		/* Case01: targetNodeInBucket->bExist == false */
		if (!targetNodeInBucket->bExist)
		{
			printf("[%s/%s] %s\n", "Failed", "Contain", "Invalid value in bucket.");
			return false;
		}

		/* Case02: targetNodeInBucket->bExist == true */
		Node* targetNode = targetNodeInBucket;
		while (true)
		{
			if (targetNode->HashKey != hashkey)
			{
				printf("[%s/%s] %s\n", "Error", "Contain", "HashKey mismatch.");
				return false;
			}

			if (targetNode->Key == InKey)
			{
				printf("[%s/%s] %s\n", "Complete", "Contain", "Contain complete.");
				return targetNode;
			}

			if (!targetNode->NextNode)
			{
				printf("[%s/%s] %s\n", "Failed", "Contain", "Invalid next node.");
				return false;
			}
			else
			{
				targetNode = targetNode->NextNode;
				continue;
			}
		}

		printf("[%s/%s] %s\n", "Failed", "Find", "Undefined.");
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

			if (targetNode->Key == InKey && targetNode->Value == InValue)
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

private:
	bool DeleteNode(Node* InNode)
	{
		if (!InNode)
		{
			printf("[%s/%s] %s\n", "Failed", "DeleteNode", "Invalid node.");
			return false;
		}

		Node* cachedPrev = InNode->PrevNode;
		Node* cachedNext = InNode->NextNode;

		if (!cachedPrev)
		{
			// InNode is `node in Bucket` (LinkedList Head)
			if (InNode == (BaseNode + InNode->HashKey))
			{
				if (cachedNext)
				{
					InNode->bExist = cachedNext->bExist;
					InNode->HashKey = cachedNext->HashKey;
					InNode->Key = cachedNext->Key;
					InNode->Value = cachedNext->Value;
					InNode->PrevNode = nullptr;
					InNode->NextNode = cachedNext->NextNode;

					cachedNext->bExist = false;
					cachedNext->HashKey = 0;
					cachedNext->Key = 0;
					cachedNext->Value = 0;
					cachedNext->PrevNode = nullptr;
					cachedNext->NextNode = nullptr;

					delete cachedNext;

					--Size;

					return true;
				}
				else
				{
					InNode->bExist = false;
					InNode->HashKey = 0;
					InNode->Key = 0;
					InNode->Value = 0;
					InNode->PrevNode = nullptr;
					InNode->NextNode = nullptr;

					// Node is not delete

					--Size;

					return true;
				}
			}

			printf("[%s/%s] %s\n", "Failed", "DeleteNode", "Undefined.");
			return false;
		}
		else // CachedPrev is Valid
		{
			if (cachedNext)
			{
				cachedPrev->NextNode = cachedNext;
				cachedNext->PrevNode = cachedPrev;
			}
			else // CachedPrev is Invalid
			{
				cachedPrev->NextNode = nullptr;
			}
		}

		InNode->bExist = false;
		InNode->HashKey = 0;
		InNode->Key = 0;
		InNode->Value = 0;
		InNode->PrevNode = nullptr;
		InNode->NextNode = nullptr;

		delete InNode;

		--Size;

		return true;
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
	bool Remove(size_t InKey, int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Remove", "BaseBucket is InValid.");
			return false;
		}

		return BaseBucket->Remove(InKey, InValue);
	}

public:
	bool Contain(int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Contain", "BaseBucket is InValid.");
			return false;
		}

		return BaseBucket->Contain(InValue);
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