
`CustomVector(const CustomVector&) = delete;`
`CustomVector& operator=(const CustomVector&) = delete;`

---

`A(const A&)` : 복사 생성자
- 새 객체를 만드는 순간 호출됨
- 새 객체를 만들 때 인자로 주어진 객체를 복사하여 새 객체를 만듦

```cpp
CustomVector<int> a;
CustomVector<int> b = a;   // 복사 생성자
CustomVector<int> c(a);    // 복사 생성자
```


 `A& operator=(const A& rhs)` : 복사 대입 생성자
- "이미 존자해는 객체"에 "값을 덮어쓰는 순간" 호출됨
- 반환타입: `A&`
- 왼쪽 피연산자(`lhs`): 멤버함수이므로 `*this` (호출객체)
- 오른쪽 피연산자(`rhs): 매개변수 `const A& rhs`:
- `operator=`는 왼쪽 피연산자를 `this`로 강제함
  
```cpp
CustomVector<int> a;
CustomVector<int> b;
b = a;                     // 복사 대입 연산자
```

---

