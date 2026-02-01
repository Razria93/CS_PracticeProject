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
	float LoadFactor;

public:
	Bucket(size_t InSize)
	{
		BaseNode = new Node[InSize];
		Capacity = InSize;
		Size = 0;
		LoadFactor = 0.f;
	}

	~Bucket()
	{
		Clear();

		delete[] BaseNode;

		BaseNode = nullptr;
		Capacity = 0;
		Size = 0;
		LoadFactor = 0.f;
	}

public:
	bool IsEmpty() { return Size == 0; }
	size_t GetSize() { return Size; }
	size_t GetCapacity() { return Capacity; }
	float GetLoadFactor() { return Capacity > 0 ? static_cast<float>(Size) / static_cast<float>(Capacity) : 0.f; }

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

public:
	void Clear()
	{
		// [Policy] No duplicates allowed

		if (!BaseNode)
		{
			printf("[%s/%s] %s\n", "Error", "Clear", "BaseBucket is invalid.");
			return;
		}

		size_t count = 0;
		Node* targetNode = BaseNode;

		while (count < Capacity)
		{
			if (targetNode && targetNode->bExist)
			{
				DeleteNode(targetNode);
			}
			else
			{
				++count;
				targetNode = BaseNode + count;
			}
		}
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
	float MaxLoadFactor;

public:
	HashTable()
	{
		BaseBucket = nullptr;
		MaxLoadFactor = 0.f;
	}

	~HashTable()
	{
		Clear();

		delete BaseBucket;

		BaseBucket = nullptr;
		MaxLoadFactor = 0.f;
	}

public:
	bool IsEmpty() { return BaseBucket ? BaseBucket->IsEmpty() : false; }
	size_t GetSize() { return BaseBucket ? BaseBucket->GetSize() : 0; }
	size_t GetCapacity() { return BaseBucket ? BaseBucket->GetCapacity() : 0; }
	float GetLoadFactor() { return BaseBucket ? BaseBucket->GetLoadFactor() : 0.f; }

public:
	void Initialize()
	{
		if (BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Initialize", "BaseBucket is already initialized.");
			return;
		}

		BaseBucket = new Bucket(2);
		MaxLoadFactor = 0.7f;
		printf("[%s/%s] bucket: %s | max-loadfactor: $f\n", "Complete", "Initialize", "Initialize complete.", BaseBucket, MaxLoadFactor);
	}

public:
	bool Insert(size_t InKey, int InValue)
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Insert", "BaseBucket is InValid.");
			return false;
		}

		if (BaseBucket->GetLoadFactor() > MaxLoadFactor)
		{
			Resize();
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

public:
	void Resize()
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Resize", "BaseBucket is InValid.");
			return;
		}

		if (BaseBucket->GetLoadFactor() > MaxLoadFactor)
		{
			size_t nextSize = BaseBucket->GetCapacity() + 1;

			while (true)
			{
				if (IsPrime(nextSize))
				{
					if (nextSize < BaseBucket->GetCapacity())
					{
						printf("[%s/%s] %s\n", "Error", "Resize", "New capacity is smaller than current capacity (Overflow).");
						return;
					}

					printf("[%s/%s] %s | before: %zd | after: %zd\n", "Complete", "Resize", "Find next size.", BaseBucket->GetCapacity(), nextSize);
					break;
				}

				++nextSize;
				continue;
			}

			Bucket* newBucket = new Bucket(nextSize);

			size_t count = 0;
			Node* targetNode = BaseBucket->BaseNode;

			while (count < BaseBucket->Capacity)
			{
				if (targetNode && targetNode->bExist)
				{
					newBucket->Insert(targetNode->Key, targetNode->Value);
					targetNode = targetNode->NextNode;
				}
				else
				{
					++count;
					targetNode = BaseBucket->BaseNode + count;

					continue;
				}
			}

			Bucket* oldBucket = BaseBucket;

			BaseBucket = newBucket;
			delete oldBucket;

			printf("[%s/%s] %s | capacity: %zd | size: %zd | loadfactor: %f\n", "Complete", "Resize", "Resize complete.", BaseBucket->GetCapacity(), BaseBucket->GetSize(), BaseBucket->GetLoadFactor());
			return;
		}

		printf("[%s/%s] %s | capacity: %zd | size: %zd | loadfactor: %f\n", "Note", "Resize", "Resizing not required.", BaseBucket->GetCapacity(), BaseBucket->GetSize(), BaseBucket->GetLoadFactor());
		return;
	}

public:
	void Clear()
	{
		if (!BaseBucket)
		{
			printf("[%s/%s] %s\n", "Error", "Remove", "BaseBucket is InValid.");
			return;
		}

		BaseBucket->Clear();
	}

public:
	bool IsPrime(size_t InSize)
	{
		// Detail: 

		if (InSize <= 1) return false;
		if (InSize <= 3) return true;	// 2, 3
		if (InSize % 2 == 0 || InSize % 3 == 0) return false;

		// Check 6k +/- 1 pattern 
		for (size_t i = 5; i * i <= InSize; i += 6)
		{
			if (InSize % i == 0 || InSize % (i + 2) == 0) return false;
		}
		return true;
	}
};