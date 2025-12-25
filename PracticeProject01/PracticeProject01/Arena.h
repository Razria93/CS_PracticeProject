#pragma once

#include "GlobalStructure.h"

class Arena
{
public:
	Arena();
	Arena(uint64_t InContainerSize);

	~Arena();

public:
	uint64_t ContainerSize;
	int ContainerCount;

private:
	// Container
	Unit* ContainerStart;
	int* ContainerValidIndices;

	int AroundCount;
	bool bIsEndFlag;

public:
	void Initialize(uint64_t InContainerSize);

public:
	void Add_Monster(StatusData InStatusData);
	void Delete_Monster(int InUnitIndex);

public:
	void GoToAround();
	void StartGame();

public:
	void Print_Container_Ptr();
	void Print_Container_Size();
	void Print_Container_Count();
	void Print_Container_Member();

	void Print_Unit_Ptr(Unit* InUnit);
	void Print_Unit_MonsterPtr(Unit* InUnit);
	void Print_Unit_Index(Unit* InUnit);
	void Print_Unit_MonsterName(Unit* InUnit);

	void Print_Monster_highestHP();
	void Print_Monster_StatusData(int InUnitIndex);
	void Print_Monster_StatusData(const char* InName, uint64_t InSize);

private:
	void Add_ValidIndex(int InUnitIndex);
	void Delete_ValidIndex(int InUnitIndex);

private:
	Unit* Find_Monster(int InUnitIndex);
	Unit* Find_Monster(const char* InName, uint64_t InSize);

private:
	bool Check_Container_IsValid();
	bool Check_Monster_IsAlive(int InUnitIndex);
	bool Check_Monster_IsAlive(const char* InName, uint64_t InSize);
}; 