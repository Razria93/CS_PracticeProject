## 동적 배열에 대한 정의

1. **지정된 형식의 요소**를 선형 배열에 저장

2. 지정한 자료형에 따라서 구조가 달라져야 함 (Template 사용 / 특수화)
	- bool을 제외한 기본 자료형의 경우: 
		- 데이터를 값(value)으로 저장  
	- bool의 경우: 
		- bit 연산을 기반으로 한 비트 단위의 데이터 저장
	- class나 struct의 경우 [구현 보류]
		- 동적 할당으로 객체를 생성 후 포인터로 저장
		- 해당 방식의 경우 해제할 때 반드시 delete 혹은 free


3. 모든 요소에 대한 빠른 임의 액세스를 허용함 (entry 포인터 & index 기반의 offset 방식)
  
4. 배열의 구조가 연속적이여야 함
	
5. 동적 배열은 인덱스 구분 없이 삽입/삭제가 가능해야 함   
	- index / value의 매핑구조에서 value가 null 값이 되는 곳이 없어야 함
		
	- 배열의 크기가 가변적이며 새로운 요소가 추가되었을 때, 
		- 할당되지 않은 배열의 인덱스보다 추가되는 인덱스의 크기가 클 경우: 
			- 남은 인덱스가 추가된 요소의 1.5배(임의값) 크기가 되도록 새로운 배열을 만듦
		
	- 중간 요소가 삽입/삭제가 될 수 있음
			- 삽입/삭제가 이루어진 위치가 배열의 마지막일 경우 [O(1)]
			 - 재할당 과정 없이 기존의 배열에서 삽입/삭제
			   
		 - 삽입/삭제가 이루어진 위치가 배열의 중간일 경우 [O(n)]
			 - 새로운 배열을 만들고 지정한 인덱스를 기준으로 이전의 인덱스(`Pre-index`)들의 요소는 같은 인덱스에 할당
			 - 해당 인덱스에 새로운 데이터를 할당
			 - 이후의 인덱스(Post-index)들의 요소는 기존의 인덱스값 + 추가된 요소의 개수의 인덱스로 재할당
			 - 작업이 완료된 배열의 포인터를 벡터의 포인터로 교체하고 기존의 배열은 초기화 후 삭제
			   
		 - 삽입/삭제가 이루어진 위치가 배열의 시작일 경우 [O(n)]
			 - 새로운 배열을 만들고 새로운 데이터를 시작 인덱스에 할당함
			 - 기존의 요소들은 기존의 인덱스값 + 추가된 요소의 개수의 인덱스로 재할당
			 - 작업이 완료된 배열의 포인터를 벡터의 포인터로 교체하고 기존의 배열은 초기화 후 삭제
  
---
## 구현구조

### 자료구조
- void*  Data 		: 현재 벡터의 시작포인터 (자료형 상관없이 저장할 수 있어야하므로 void*)
- size_t Offset		: 현제 벡터에서 사용하는 자료형의 크기
- size_t Capacity	: 현재 벡터의 할당 가능한 총 원소 갯수
- size_t Size		: 현재 벡터의 할당 된 총 원소 갯수

### 함수
- vector(), ~vector() 		: 생성 / 소멸자
- capcity() 				: 현재 할당 가능한 총 원소 갯수
- size()					: 현재 할당 된 총 원소 갯수
- empty()					: 현재 할당 된 원소의 갯수가 없는지 체크
- push_back() / pop_back()  : 맨 뒤에 원소를 붙임 / 제거
- clear()					: 모든 요소 제거 (Size == 0)
- resize()					: 벡터의 크기 재조정하여 재할당
- operator[]				: 배열의 특정 원소에 [] 기호를 가지고 접근
- data()					: 벡터의 시작 포인터
- insert()					: 원소 삽입
- erase()					: 원소 삭제
- swap()					: 원소 교환
- begin(), end()			: 반복자 (순회하며 접근하는 반복문에서 필요한 접근 수단)

---

### std::vector 구조 예제

```cpp
#include <vector>
#include <iostream>
#include <string>

int main()
{
    // 1) 초기화(생성)
    std::vector<int> v0;                 // empty (size=0)
    std::vector<int> v1(5);              // size=5, 값은 0으로 value-init
    std::vector<int> v2(5, 7);           // size=5, 모든 값 7
    std::vector<int> v3{1, 2, 3, 4};     // initializer_list
    std::vector<int> v4 = v3;            // 복사(copy)
    std::vector<int> v5 = std::move(v3); // 이동(move), v3는 "유효하지만 상태 미정(보통 비어짐)"

    // 2) 조회(상태/포인터)
    std::cout << "v2 size=" << v2.size() << " cap=" << v2.capacity() << "\n";
    std::cout << "v2 data=" << (const void*)v2.data() << "\n"; // 내부 버퍼 시작 주소(없으면 nullptr일 수도)

    // 3) 추가(push_back / emplace_back)
    std::vector<std::string> s;
    s.push_back("A");            // 복사/이동으로 추가
    s.emplace_back(3, 'x');      // "xxx" 직접 생성(생성자 인자 전달)

    // 4) 할당 변경(대입 / assign)
    std::vector<int> a{1,2,3};
    std::vector<int> b{9,9};

    b = a;                       // 대입(복사) : b의 내용이 a로 교체
    b = {10, 20};                // initializer_list 대입
    b.assign(4, 5);              // size=4, 모두 5로 채움
    b.assign(a.begin(), a.end()); // range assign

    // 5) 수정(삽입/삭제)
    std::vector<int> x{10, 20, 30, 40};

    x.insert(x.begin() + 1, 15);       // 10, 15, 20, 30, 40
    x.erase(x.begin() + 2);            // (0-based) 20 제거 -> 10, 15, 30, 40
    x.erase(x.begin(), x.begin() + 2); // 앞 2개 제거 -> 30, 40

    // 6) pop_back / clear
    x.push_back(50);   // 30, 40, 50
    x.pop_back();      // 30, 40  (마지막 1개 제거)
    x.clear();         // size=0 (capacity는 유지될 수 있음)

    // 7) 용량 관리(reserve / shrink_to_fit / resize)
    std::vector<int> r;
    r.reserve(100);    // capacity >= 100 확보(재할당/복사 비용 줄이기 목적)
    r.resize(3);       // size=3 (값은 0으로 채워짐)
    r.resize(5, 7);    // size=5, 새로 늘어난 2개는 7
    r.resize(2);       // size=2로 축소(뒤 원소 제거)

    r.shrink_to_fit(); // 구현에 따라 capacity를 size에 맞춰 줄이려 "요청"(보장 아님)

    // 8) swap (교체) / 실제 메모리 해제 트릭
    std::vector<int> m(1000, 1);
    std::vector<int>().swap(m);  // m을 빈 벡터와 swap → m의 capacity까지 사실상 비우는 패턴(자주 쓰임)

    // 9) 범위 기반 루프 / 인덱싱
    std::vector<int> p{1,2,3};
    for (int& e : p) e *= 10;    // 10,20,30
    std::cout << p[0] << "\n";   // 10 (범위 체크 없음)
    std::cout << p.at(0) << "\n"; // 10 (범위 체크, 예외 발생 가능)

    return 0;
}

```