# Root 삭제 후 서브트리 유실 이슈

## 개요

### 발생일시
- 2026.01.24

### 이슈종류
- 버그

### 진행상태
- [x] 해결

### 브랜치명
- feature/binary-search-tree


---

## 요약
- `BinarySearchTree::Erase()`에서 **Root 노드 삭제 시 Root를 교체 노드로 갱신하지 않아**, 삭제 이후 트리가 비어있는 것처럼 동작함
- 또한 `Delete()`가 `Parent/Left/Right`를 `nullptr`로 초기화하기 때문에 **Root의 서브트리가 소실**되어 순회 시 노드가 누락됨


---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::string 등) 사용 제한 환경


---

## 이슈재현

`main.cpp`
```cpp
BinarySearchTree bst;

bst.Insert(50);
bst.Insert(30);
bst.Insert(70);
bst.Insert(60);
bst.Insert(80);

bst.Erase(50);      // Root 삭제
bst.TraverseInOrder();
```

`BinarySearchTree.h`
```cpp
// Erase
// Root 삭제 시 Root 갱신 없이 switchNode->Parent만 nullptr로 설정
else
{
	switchNode->Parent = nullptr;
}
```

---

## 실행결과
```
NOTE                 : InValid Root.
```
- Root가 `nullptr`로 남아 트리가 비어있는 것으로 인식됨
- 기대했던 나머지 노드(30, 60, 70, 80)가 출력되지 않음


---

## 근본 원인

1. `Delete()`가 삭제 대상 노드의 `Parent/Left/Right`를 `nullptr`로 초기화함
2. Root 삭제 시 `Root = switchNode`로 갱신하지 않아, Root가 `nullptr`로 유지됨
3. 삭제 전 Root의 `Left/Right`를 캐싱하지 않아 서브트리 연결 정보가 소실됨


---

## 수정제안

- Root 삭제 시 `Root = switchNode`로 교체 노드를 명시적으로 지정
- 삭제 전에 `leftNode_cached`, `rightNode_cached`로 서브트리를 캐싱한 뒤 교체 노드에 재연결
- 삭제 대상의 부모 링크를 먼저 끊어 순회 시 루프/잘못된 링크를 방지

```cpp
Node* leftNode_cached = eraseNode->Left;
Node* rightNode_cached = eraseNode->Right;

// ... 중략 ...

Delete(eraseNode);

// Root 교체
Root = switchNode;
switchNode->Parent = nullptr;

// 서브트리 재연결
switchNode->Left = leftNode_cached;
leftNode_cached->Parent = switchNode;

switchNode->Right = rightNode_cached;
rightNode_cached->Parent = switchNode;
```

---

## 수정확인

```cpp
BinarySearchTree bst;

bst.Insert(50);
bst.Insert(30);
bst.Insert(70);
bst.Insert(60);
bst.Insert(80);

bst.Erase(50);
bst.TraverseInOrder();
```

---

## 실행결과
```
30 60 70 80
```


---
