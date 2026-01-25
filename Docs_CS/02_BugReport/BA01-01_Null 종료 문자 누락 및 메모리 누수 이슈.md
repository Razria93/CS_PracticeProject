# MyString '\0' 문자 누락 및 메모리 누수 발생

## 개요

### 발생일시
- 2026.01.20

### 이슈종류
- 버그

### 진행상태
- [x] 해결

### 브랜치명
- feature/mystring


---

## 요약
- `MyString`에서 새 버퍼를 할당할 때 **널 종료문자('\0')를 확보하지 않아 문자열이 손상**됨  
- 새 버퍼를 할당한 뒤 **기존 버퍼를 해제하지 않아 메모리 누수**가 발생함  
- 버퍼 크기를 `+1`로 확장하고, 재할당 전에 `Clear()`로 기존 메모리를 해제하여 해결


---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::string 등) 사용 제한 환경


---

## 이슈재현

```cpp
MyString str01("Hello");
str01.Append("World");
str01.Print();
```


---

## 실행결과
```
HelloWorld???    // 널 종료 누락으로 인해 출력이 깨짐
```


---

## 근본 원인

1. **버퍼 크기를 문자열 길이만큼만 할당**함  
   - `new char[length]`로 할당되어 널 종료문자를 넣을 공간이 없음  
   - 출력/연산 시 버퍼 범위를 넘는 접근이 발생해 문자열이 손상됨
2. **재할당 시 기존 버퍼를 해제하지 않음**  
   - `Base`를 새 버퍼로 덮어쓰며 기존 버퍼가 누수됨


---

## 수정

- 새 버퍼 크기를 `length + 1`로 할당
- 복사 완료 후 `newBase[length] = '\0'` 추가
- `Clear()`로 기존 버퍼를 해제한 뒤 새 버퍼를 대입

```cpp
char* newBase = new char[length + 1];

for (size_t i = 0; i < length; ++i)
{
	newBase[i] = *(s + i);
}

newBase[length] = '\0';
Clear();

Base = newBase;
Length = length;
```


---

## 수정확인

```cpp
MyString str01("Hello");
str01.Append("World");
str01.Print();
```


---

## 실행결과
```
HelloWorld
```


---