## 이진 탐색 트리에 대한 이해

- 계층적 자료구조
- 그래프의 일종 (노드와 간선으로 이루어짐)
	- 단방향성 그래프
	- 부모-자식으로 노드의 관계가 형성됨
	- Root 노드를 제외한 모든 노드는 부모노드는 1개만 가질 수 있음 (일반트리)
	- 모든 노드는 최대 2개(0~2)의 자식만 가질 수 있음. (이진트리)
	- 각 노드는 좌측에 자기보다 작은 수를, 우측에 자기보다 큰 수를 배치함 (이진탐색트리)
	- 즉, 자료를 저장할 때 정렬을 하는 이진 트리라는 것

---
## 최소 구현 API

```cpp
template<typename T>
class BinarySearchTree
{
public:
    size_t Size() const;
    bool Empty() const;
    void Clear();

    bool Insert(const T& value);
    bool Find(const T& value) const; 
    bool Erase(const T& value);

    template<typename T>
    void TraversePreOrder(T visit) const;

    template<typename F>
    void TraverseInOrder(T visit) const;

    template<typename F>
    void TraversePostOrder(T visit) const;
};
```