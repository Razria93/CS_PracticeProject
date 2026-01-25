# MyString::Interleave(..) 에서의 size_t 언더플로우 이슈

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
- `MyString::Interleave()`에서 `size_t` 길이 차이를 직접 빼면서 **언더플로우가 발생**해 잘못된 길이를 계산함  
- 길이가 작은 문자열에서 큰 문자열을 빼면 매우 큰 값이 되어 **루프 범위를 초과하고 메모리를 오염**시킴  
- 길이 비교 후 **절대값을 별도 계산**하도록 수정하여 해결


---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::string 등) 사용 제한 환경


---

## 이슈재현

```cpp
MyString str01("ABC");
str01.Interleave("0123456789");
str01.Print(); // `A0B1C23456789`를 의도함
```


---

## 실행결과
```cpp
CS_Assignment01.exe(프로세스 225540)이(가) -1073741819 코드(0xc0000005)와 함께 
종료되었습니다. (Crash)
```


---

## 근본 원인

1. **`size_t`는 음수를 표현하지 못함**  
   - `Length - length`를 직접 계산하면 작은 값에서 큰 값을 빼는 순간 언더플로우 발생
2. **언더플로우된 값이 루프 범위로 사용됨**  
   - 매우 큰 값으로 인식되어 인덱스가 범위를 벗어남
   - 결과적으로 버퍼 오염 및 출력 깨짐 발생


---

## 수정

- 길이 비교 후 큰 쪽을 기준으로 `lengthSubtract`를 계산
- `bool bIsLarge`와 `int lengthSubtract`로 길이 차이를 안전하게 분리

```cpp
bool bIsLarge = (int)(Length - length) > 0 ? true : false;
int lengthSubtract = bIsLarge ? (int)(Length - length) : (int)(length - Length);

for (size_t i = 0; i < newLength - lengthSubtract; ++i)
{
	bool shift = (i % 2 != 0) ? true : false;
	size_t idx = i / 2;

	if (shift == false)
	{
		newBase[i] = Base[idx];
	}
	else
	{
		newBase[i] = *(s + idx);
	}
}
```


---

## 수정확인

```cpp
MyString str04("Shift");
str04.Interleave("Change");
str04.Print();
```


---

## 실행결과
```
SChhiafntge
```


---