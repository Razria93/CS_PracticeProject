# Dangling Pointer 이슈

## 개요

### 발생일시
- 2025.12.11

### 이슈종류
- 버그

### 진행상태
- [x] 해결

### 브랜치명
- feature/monster

---

## 요약
- `delete` 후 포인터가 `nullptr`로 변경되지 않아 **Dangling Pointer** 문제가 발생함  
- 포인터를 명시적으로 `nullptr`로 초기화하여 해결

---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::string 등) 사용 제한 환경

---

## 이슈재현

```cpp
Monster* temp = new Monster;
delete temp;

if (temp == nullptr)
{
    printf("temp is nullptr\n");
}
else
{
    printf("temp is not nullptr\n");
}
```

---

## 실행결과
```
temp is not nullptr
```

## 근본 원인

1. delete는 할당된 메모리만 해제하며, 포인터 변수(temp) 자체의 값을 변경하지 않음
2. 따라서 포인터는 해제된 메모리를 가리키는 Dangling Pointer 상태가 됨
3. 이후 nullptr check가 의도와 다르게 진행되어 잘못된 포인터 접근이 발생함

## 수정

포인터 `delete` 후 명시적으로 nullptr 대입
```cpp
Monster* temp = new Monster;

delete temp;
temp = nullptr;   
```

## 수정확인

`delete` 이후 `nullptr`를 명시적으로 대입
```cpp
Monster* temp = new Monster;
delete temp;
temp = nullptr;

if (temp == nullptr)
{
    printf("temp is nullptr\n");
}
else
{
    printf("temp is not nullptr\n");
}
```

## 실행결과
```
temp is nullptr
```