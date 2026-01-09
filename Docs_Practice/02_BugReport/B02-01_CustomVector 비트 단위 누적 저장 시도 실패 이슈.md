# CustomVector 비트 단위 누적 저장 시도 실패 (bool 저장 단위 한계 + 런타임 타입 판별 분기)

## 개요

### 발생일시
- 2025.12.28
    

### 이슈종류
- [x] 버그(개념/타입 오해 기반)
    

### 진행상태
-  Pending (리팩토링/특수화 예정)
    

### 브랜치명
- feature/pp-vector-extend


---

## 요약
- `CustomVector<T>`에서 `T=bool`인 경우에도 `Size/Capacity`는 공통으로 유지하고, `bitIndex / byteIndex` 변환 함수로 **저장 위치(바이트 인덱스, 비트 인덱스)를 계산**하여 `|` 연산으로 비트를 누적 저장하는 형태를 시도함
    
- `T=bool` 여부는 템플릿 특수화가 아니라, `IsTypeBoolean()` 같은 함수로 **런타임에서 타입을 판별하여 분기 처리**하려고 구성함 
  (`if (IsTypeBoolean()) { bool 전용 처리 } else { 일반 처리 }` 구조)
    
- 그러나 저장소 타입이 `T*`(즉 `bool*`)인 상태에서는, `bool` 원소가 **0/1(참/거짓)만 표현하는 단일 논리값**이므로 “1바이트에 8비트 누적” 같은 비트 패턴 저장이 성립하지 않음
    
- 결론적으로 “비트팩”을 하려면 저장소 원소 타입이 `bool`이 아니라 `uint8_t / uint32_t / uint64_t` 같은 **비트 컨테이너 타입**이어야 함을 학습함
    
- 이후 `CustomVector<bool>` 템플릿 특수화로 저장소를 별도 설계하고, 런타임 타입 판별 분기
  (`IsTypeBoolean`)는 제거할 예정
    

---

## 개발환경

- IDE: Visual Studio 2022
- C++17
- 커스텀 컨테이너 구현 학습 목적


---

## 이슈재현

### `main`

```cpp
CustomVector<bool> v;

for (int i = 0; i < 4; i++)
{
    v.push_back(true);
}

v.PrintData();
```

### `CustomVector<bool>::push_back` (의도한 핵심 아이디어)

```cpp
size_t byteIndex = index / 8;
size_t bitIndex  = index % 8;

// 해당 byte 위치에 bit를 누적 저장하려는 의도
Data[byteIndex] = Data[byteIndex] | (InData << bitIndex);
```

### 런타임 타입 판별 분기(의도)

```cpp
if (IsTypeBoolean())
{
    // bool 전용: bitIndex/byteIndex 기반 비트 누적 저장 시도
}
else
{
    // 일반 타입: 일반적인 벡터 push_back 로직
}
```

---

## 기대 동작(의도)

- `Size/Capacity`는 기존 벡터와 동일하게 관리
    
- push_back 시마다 “요소 인덱스”를 `byteIndex/bitIndex`로 변환하여 **같은 바이트에 여러 bool 값을 비트 단위로 누적 저장** (예: 0~7번째 bool → Data[0]의 각 비트에 저장)
    
- bool 여부는 `IsTypeBoolean()` 함수로 판단하여, 같은 클래스 내에서 분기로 처리하려 했음

---

## 실제 동작(문제)

- 저장소가 `bool*`이므로 `Data[byteIndex]` 자체가 **bool 1개(0/1)** 임
    
- 따라서 `Data[byteIndex] | (1 << bitIndex)` 같은 연산을 해도  
    결과는 결국 `true` 또는 `false`로 축약됨
    
- 즉, “비트 패턴(예: 00010000 같은 형태)”을 유지한 채로 누적 저장이 불가능
    

---

## 근본 원인

### 1) `bool`은 비트 컨테이너가 아니라 단일 논리값 타입

- `bool` 한 원소는 “여러 비트를 담는 그릇”이 아님
    
- 비트 연산 결과가 최종적으로 `bool`로 대입되는 순간  
    저장 가능한 상태는 `0` 또는 `1`로 제한됨
    
- 따라서 “bitIndex를 바꿔가며 누적 저장”이라는 아이디어가  
    `bool*` 저장소 위에서는 성립할 수 없음
    

### 2) 런타임 타입 판별 분기(`IsTypeBoolean`)는 해결책이 될 수 없음

- `IsTypeBoolean()`로 `T=bool`을 알아내더라도,  
    **저장소가 `bool*`인 한 비트 누적 저장이 불가능**하다는 근본 원인은 그대로 유지됨
    
- 즉, “분기 자체”가 문제가 아니라 **bool 저장소 타입 선택이 비트팩 목적과 불일치**한 것이 핵심


---

## 수정 방향(예정)

### 1) 저장소 타입을 비트 컨테이너로 변경

- `CustomVector<bool>` 전용 저장소를 `uint8_t*`(또는 `uint64_t*`)로 구성

- `Size/Capacity`는 “bit 단위”로 유지하고, 내부에서만 변환 수행


예시(방향성)

```cpp
template<>
class CustomVector<bool>
{
private:
    uint8_t* Data;   // bit container
    size_t Capacity; // bits
    size_t Size;     // bits
};
```

### 2) 템플릿 특수화로 분리 (런타임 분기 제거)

- 일반 `CustomVector<T>`와 `CustomVector<bool>`의 저장 방식이 다르므로  
    `IsTypeBoolean()` 같은 런타임 분기 대신 컴파일 타임 분리로 구현 예정


---

## 수정 필요 체크리스트(후속 작업)

-  `CustomVector<bool>` 템플릿 특수화 생성
    
-  저장소를 `uint8_t*` 또는 `uint64_t*`로 변경
    
-  `bitIndex/byteIndex` 계산 및 set/get 구현
    
-  `push_back/insert/erase`는 비트 단위 이동/복사 로직으로 재작성
    
-  기존 `IsTypeBoolean()` 기반 런타임 분기 제거
    

---