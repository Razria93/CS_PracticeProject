# HashTable Bucket 탐색 루프에서 해시 충돌 해결 중 무한 루프 이슈

## 개요

### 발생일시
- 2026.01.31

### 이슈종류
- 버그

### 진행상태
- [x] 해결

### 브랜치명
- feature/hash-table


---

## 요약

- 해시 함수가 `InKey % Capacity` 형태로 구현되어 있어, 서로 다른 Key 값이 동일한 `HashKey`를 가지는 **정상적인 해시 충돌 상황**이 발생함

- `(1, 100)` 과 `(11, 100)`이 동일한 `HashKey`를 가지고 있어 같은 버킷에 `Chaining`되어야 하는 상태에서 `Bucket::Insert()` 내부의 버킷 탐색 루프를 `Key` 일치여부와 `Value` 일치여부를 별도로 체크하게 구성하였던 상태
  
- 이 때, `Key`가 불일치 할 경우, `NextNode`의 유효성을 체크하고 다음과 같이 작동했어야 함
	- `NextNode`가 존재하지 않을경우: `NewNode`를 생성하여 초기화하고 추가함
	- `NextNode`가 존재할 경우: `NextNode`를 다음 `TargetNode`로 저장함

- 그러나 유효성 체크와 다음 `TargetNode` 설정을 하지 않고 `continue`만 사용하였으며, 결과적으로 무한 루프가 발생함

- 탐색 조건을 `Key + Value` 단일 비교로 통합하고,  모든 반복 경로에서 노드 전진이 보장되도록 수정하여 문제를 해결함

- 해당 문제가 `Find()`에도 동일하게 잠재되어 있어 동일한 방식으로 수정함


---

## 개발환경

- IDE: Visual Studio 2022
- C++17
- 사용자 정의 HashTable / Bucket / Node 구현 중
- Separate Chaining 방식 사용
- 해시 함수: `InKey % Capacity` 사용


---

## 이슈재현

```cpp
// Capacity = 10
hashTable->Insert(1,  100);
hashTable->Insert(11, 100); // 1 % 10 == 11 % 10
```


---

## 실행결과

```text
[Insert]
[Complete/Insert] Insert complete: <1, 100> | Size: 1
[Complete/Insert] Insert complete: <2, 200> | Size: 2
[Complete/Insert] Insert complete: <3, 300> | Size: 3
[Complete/Insert] Insert complete: <2, 300> | Size: 4
[Failed/Insert] Duplicate entries are not allowed: <2, 300> | Size: 4

[Infinite Loop..]
```

- `hashTable->Insert(11, 100)` 내부 while 루프가 종료되지 않음
- 논리적 무한 루프 발생


---

## 근본 원인

1. **Modulo 기반 해시 함수로 인한 정상적인 해시 충돌**
    
    - `GetHash(InKey) = InKey % Capacity`
    - 서로 다른 Key(1, 11)가 동일한 버킷 인덱스를 가짐
        
2. **Key 불일치 분기에서 포인터 전진 누락**
    
```cpp
Node* targetNode = targetNodeInBucket;

while (true)
{
	if (targetNode->HashKey != hashkey)
	{
		return false;
	}

	// Bug Point
	if (targetNode->Key != InKey)
	{
		continue;
	}

	if (targetNode->Value == InValue)
	{
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

		return true;
	}
	else
	{
		targetNode = targetNode->NextNode;
		continue;
	}
}
```
    
    - `continue`로 인해 반복문의 다음 사이클로 진입
    - `targetNode`가 갱신되지 않아 동일 노드를 다시 검사함
        
3. **반복 제어 흐름 붕괴**
    
    - `NextNode`로 이동하는 로직이 `Key` 일치 이후 분기에만 존재
    - `Key` 불일치 상태에서는 탐색이 정지된 채 반복됨


---

## 수정

- Key 불일치 전용 `continue` 분기 제거
- 탐색 성공 조건을 **Key + Value 동시 일치 조건**으로 통합
- 일치하지 않는 경우 항상 다음 노드로 전진하도록 반복 구조를 단순화
    

```cpp
Node* targetNode = targetNodeInBucket;

while (true)
{
	if (targetNode->HashKey != hashkey)
	{
		return false;
	}

	// Bug Resolve
	if (targetNode->Key == InKey && targetNode->Value == InValue)
	{
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

		return true;
	}
	else
	{
		targetNode = targetNode->NextNode;
		continue;
	}
}
```


---

## 수정확인

```cpp
// Bug Resolve
if (targetNode->Key == InKey && targetNode->Value == InValue)
{
	return false;
}
```


---

## 실행결과

```text
[Insert]
[Complete/Insert] Insert complete: <1, 100> | Size: 1
[Complete/Insert] Insert complete: <2, 200> | Size: 2
[Complete/Insert] Insert complete: <3, 300> | Size: 3
[Complete/Insert] Insert complete: <2, 300> | Size: 4
[Failed/Insert] Duplicate entries are not allowed: <2, 300> | Size: 4
[Complete/Insert] Insert complete: <11, 100> | Size: 5
...
```

- 모든 `Insert()` 호출이 정상 종료됨
- 해시 충돌로 체이닝된 노드가 존재해도 탐색이 항상 전진함
- 무한 루프 및 비정상 동작 재현되지 않음
- 모든 `Find()` 호출도 정상 종료됨


---