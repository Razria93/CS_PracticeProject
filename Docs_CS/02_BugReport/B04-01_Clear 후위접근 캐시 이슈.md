# Clear 후위접근 캐시 이슈

## 개요

### 발생일시
- 2026.01.22

### 이슈종류
- 버그

### 진행상태
- [x] 해결

### 브랜치명
- feature/binary-search-tree


---

## 요약
- `BinarySearchTree::Clear()`가 후위 순회(post-order)를 모방하기 위해 `cacheDirection`을 사용했으나, 캐시 정보가 노드에 고정되지 않아 깊은 리프 처리 이후 상위 브랜치의 캐시가 소실됨

- 브랜치 노드의 자식 포인터(2레벨) 해제 후 브랜치노드(1레벨)을 해제한 뒤, Root노드(0레벨)으로 돌아가 다음 작업을 하려고 할 때, 소실 및 노후화된 방향 정보`cacheDirection`이 적용되어 잘못된 포인터 접근이 발생, 프로세스가 `0xc0000005`로 종료됨


---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::string 등) 사용 제한 환경

---

## 이슈재현

`main.cpp`
```cpp
// main.cpp
BinarySearchTree bst;

bst.Insert(300);
bst.Insert(100);
bst.Insert(50);
bst.Insert(200);
bst.Insert(500);
bst.Insert(400);

bst.Clear();
```

`BinarySearchTee.h`
```cpp
// BinarySearchTree.h
Node* targetNode = Root;
ECacheDirection cacheDirection = ECacheDirection::None;

while (targetNode != nullptr)
{
	if (targetNode->Left)
	{
		cacheDirection = ECacheDirection::Left;
		targetNode = targetNode->Left;
	}
	else if (targetNode->Right)
	{
		cacheDirection = ECacheDirection::Right;
		targetNode = targetNode->Right;
	}
	else
	{
		Node* parent = targetNode->Parent;
		//.. 중략 .. //	
	}
}

```

---

## 실행결과

```cpp
[Clear]
...
Complete_Delete : Target: 0000021BED703850 | Size: 3
Child_Before    : Parent->Right: 0000021BED703310
Child_After     : Parent->Right: 0000000000000000

C:\Mentoring\PracticeProject\CS_PracticeProject04\x64\Debug\CS_PracticeProject04.exe(프로세스 285080)이(가) -1073741819 코드(0xc0000005)와 함께 종료되었습니다.
```


---

## 근본 원인

1. `cacheDirection`은 루프 외부에 존재하는 단일 변수이며, 특정 노드에 대한 캐시가 아니라 **마지막으로 이동한 방향만 기록**함
   
2. 깊이가 2 이상인 리프 노드 처리 후 상위 브랜치로 복귀할 때, **브랜치 노드의 캐시가 이미 소실**되어 잘못된 방향으로 부모의 자식 포인터를 갱신함
   
3. 결과적으로 해제된 노드나 잘못된 포인터를 참조하게 되어 접근 위반이 발생함


---

## 수정 제안

### 제안 1) 노드 단위 캐시 도입

- 각 `Node`에 방향 캐시 정보를 보관하여, **해당 노드의 자식 처리 후에만** 올바른 방향을 참조하도록 변경

### 제안 2) 재귀 기반 후위 순회로 전환

- `Clear()`를 재귀 함수로 구현하여, **하위 노드를 먼저 처리**한 뒤 현재 노드를 제거
- 상위 노드는 하위 노드가 완전히 정리될 때까지 대기하므로 캐시 손실 문제가 제거됨


---

## 수정확인

- 재귀 기반 `Clear()` 구현 후 동일 입력으로 실행
- 모든 노드가 순차적으로 삭제되며, 프로세스가 정상 종료되는지 확인

`main.cpp`
```cpp
// main.cpp
int main()
{
	std::printf("\n[Clear]\n");
	if (bst.Clear())
	{
		std::printf("[Clear_Complete]\n");
	}
	else
	{
		std::printf("[Clear_Failed]\n");
	}
	
	return 0;
}
```

`BinarySearchTee.h`
```cpp
// BinarySearchTee.h
public:
	bool Clear()
	{
		bool result = Clear(Root);
		
		Root = nullptr;
		Size = 0;
		
		return result;
	}
		
	bool Clear(Node* InNode)
	{
		if (!InNode) return false; // this Node is NULL
				
		if (Clear(InNode->Left))
		{
			std::printf(
			"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
			"Clear_Left", InNode->Value, InNode, InNode->Left, InNode->Parent);
		}
		else
		{
			std::printf(
			"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
			"InValid_Left", InNode->Value, InNode, InNode->Left, InNode->Parent);
		}

		if (Clear(InNode->Right))
		{
			std::printf(
			"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
			"Clear_Right", InNode->Value, InNode, InNode->Right, InNode->Parent);
		}
		else
		{
			std::printf(
			"%-15s : CurNodeValue: %-5d | CurNode: %p | Target: %p | Parent: %p\n",
			"InValid_Right", InNode->Value, InNode, InNode->Right, InNode->Parent);
		}
		
		Delete(InNode);
		
		return true;
	}
```


---

## 실행결과
```cpp
[Clear]
InValid_Left    : CurNodeValue: 50    | CurNode: 0000018C454C30E0 | Target: 0000000000000000 | Parent: 0000018C454C2C00
InValid_Right   : CurNodeValue: 50    | CurNode: 0000018C454C30E0 | Target: 0000000000000000 | Parent: 0000018C454C2C00
Clear_Left      : CurNodeValue: 100   | CurNode: 0000018C454C2C00 | Target: 0000018C454C30E0 | Parent: 0000018C454C2A80
InValid_Left    : CurNodeValue: 200   | CurNode: 0000018C454C2AE0 | Target: 0000000000000000 | Parent: 0000018C454C2C00
InValid_Right   : CurNodeValue: 200   | CurNode: 0000018C454C2AE0 | Target: 0000000000000000 | Parent: 0000018C454C2C00
Clear_Right     : CurNodeValue: 100   | CurNode: 0000018C454C2C00 | Target: 0000018C454C2AE0 | Parent: 0000018C454C2A80
Clear_Left      : CurNodeValue: 300   | CurNode: 0000018C454C2A80 | Target: 0000018C454C2C00 | Parent: 0000000000000000
InValid_Left    : CurNodeValue: 400   | CurNode: 0000018C454C2C60 | Target: 0000000000000000 | Parent: 0000018C454C2F00
InValid_Right   : CurNodeValue: 400   | CurNode: 0000018C454C2C60 | Target: 0000000000000000 | Parent: 0000018C454C2F00
Clear_Left      : CurNodeValue: 500   | CurNode: 0000018C454C2F00 | Target: 0000018C454C2C60 | Parent: 0000018C454C2A80
InValid_Right   : CurNodeValue: 500   | CurNode: 0000018C454C2F00 | Target: 0000000000000000 | Parent: 0000018C454C2A80
Clear_Right     : CurNodeValue: 300   | CurNode: 0000018C454C2A80 | Target: 0000018C454C2F00 | Parent: 0000000000000000
[Clear_Complete]
```


---