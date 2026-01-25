# char* 기반 Custom FString에서 sizeof 사용으로 발생한 문자열 길이 오류

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
- std::string / FString을 사용하지 않고 `char*` 기반의 커스텀 문자열 클래스를 구현하는 과정에서,  
  외부에서 전달된 문자열에 대해 `sizeof`를 사용하여 길이를 계산함  
- 하지만 `sizeof`는 **포인터 크기(8바이트)**만 반환하므로 실제 문자열 길이를 얻지 못해 버그 발생  
- 해결을 위해 **문자열 길이(size)를 외부에서 직접 전달받는 방식으로 리팩토링**함


---

## 개발환경
- IDE: Visual Studio 2022  
- C++17  
- 표준 문자열 라이브러리(std::vector / std::string 등) 사용 제한 환경


---

## 이슈재현
`main`
```cpp
monster->Set_Name("MONSTERNAME");
```


`class Monster`
```cpp
void Monster::Set_Name(const char* InName)
{
    // 문제 코드
    int size = sizeof(InName);  // 실제 문자열 길이가 아닌 '포인터 크기(8)' 반환

	for (i = 0; i < size; i++)
	{
		Name[i] = InName[i];
	}

    printf("Name:%s\n", Name);
}
```


---

## 실행결과
```
Name: MONSTERN袴袴袴袴袴袴袴袴
```


---

## 근본 원인

**`sizeof(InName)`의 잘못된 사용**
- InName은 char 배열이 아니라 포인터(char)*
- 따라서 sizeof(InName)은 **포인터 크기(Windows 64bit 기준 8바이트)**를 반환
- 문자열의 실제 길이를 반환하지 않음

**문자열 길이 계산 실패 → 메모리 복사 오류 발생**
- for문에 잘못된 길이를 넘김
- 문자열이 정상적으로 복사되지 않음
- 쓰레기 값(袴)이 들어감
- 널 종료문자('\0')가 누락됨
- Name에 올바른 문자열이 저장되지 않음

**이후 문자열 비교 / 출력 과정에서 예측 불가능한 동작 발생**
- 버퍼 범위를 침범해 Undefined Behavior 발생 가능


---

## 수정

문자열 길이를 외부에서 직접 전달받는 구조로 변경
```cpp
void Monster::Set_Name(const char* InName, uint64_t InSize)
{
	for (i = 0; i < InSize; i++)
	{
		M_StatusData.Name[i] = InName[i];
	}

    printf("Name:%s\n", Name);
}
```


---

## 수정확인

`main`
```cpp
monster->Set_Name("MONSTERNAME", sizeof("MONSTERNAME"));
```

`class Monster`
```cpp
void Monster::Set_Name(const char* InName, uint64_t InSize)
{
	for (i = 0; i < InSize; i++)
	{
		M_StatusData.Name[i] = InName[i];
	}

    printf("Name:%s\n", Name);
}
```


---

## 실행결과
```cpp
MONSTERNAME
```


---