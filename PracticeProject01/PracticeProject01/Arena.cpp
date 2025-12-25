#include <iostream>
#include "Arena.h"

#include "Monster.h"
#include "GlobalStructure.h"

Arena::Arena()
{
}

Arena::Arena(uint64_t InContainerSize)
{
	Initialize(InContainerSize);
}

Arena::~Arena()
{
	delete ContainerValidIndices;
	delete ContainerStart;
}

void Arena::Initialize(uint64_t InContainerSize)
{
	printf("\n-------------------------------------------\n");
	printf("[Initialize]\n");
	printf("\n");

	AroundCount = 0;
	bIsEndFlag = false;

	ContainerStart = new Unit[InContainerSize];
	ContainerValidIndices = new int[InContainerSize];

	ContainerSize = InContainerSize;
	ContainerCount = 0;

	Print_Container_Ptr();
	Print_Container_Size();
	printf("\n");

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		temp->Unit_Monster = nullptr;
		temp->Unit_Index = -1;

		ContainerValidIndices[i] = -1;

		printf("[Initialize Units %d]\n", i);
		Print_Unit_Ptr(temp);
		Print_Unit_MonsterPtr(temp);
		Print_Unit_Index(temp);
		Print_Unit_MonsterName(temp);
		printf("\n");
	}

	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::Add_Monster(StatusData InStatusData)
{
	printf("\n-------------------------------------------\n");
	printf("[Add Monster]\n");
	printf("\n");

	Monster* monster = new Monster(InStatusData);

	// monster->Initialize(InStatusData);

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		if (temp->Unit_Index == -1)
		{
			printf("[Before Add Units]\n");
			Print_Unit_Ptr(temp);
			Print_Unit_MonsterPtr(temp);
			Print_Unit_Index(temp);
			Print_Unit_MonsterName(temp);
			printf("\n");

			temp->Unit_Monster = monster;
			temp->Unit_Index = i;

			Add_ValidIndex(i);

			printf("[After Delete Units]\n");
			Print_Unit_Ptr(temp);
			Print_Unit_MonsterPtr(temp);
			Print_Unit_Index(temp);
			Print_Unit_MonsterName(temp);

			break;
		}
	}

	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::Delete_Monster(int InUnitIndex)
{
	printf("\n-------------------------------------------\n");
	printf("[Delete Monster]\n");
	printf("\n");

	Unit* temp = Find_Monster(InUnitIndex);

	printf("[Before Delete Units]\n");
	Print_Unit_Ptr(temp);
	Print_Unit_MonsterPtr(temp);
	Print_Unit_Index(temp);
	Print_Unit_MonsterName(temp);
	printf("\n");

	delete temp->Unit_Monster;

	temp->Unit_Monster = nullptr;
	temp->Unit_Index = -1;

	Delete_ValidIndex(InUnitIndex);

	printf("[After Delete Units]\n");
	Print_Unit_Ptr(temp);
	Print_Unit_MonsterPtr(temp);
	Print_Unit_Index(temp);
	Print_Unit_MonsterName(temp);

	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::GoToAround()
{
	if (bIsEndFlag) return;

	if (!Check_Container_IsValid())
		return;

	printf("\n===========================================\n");
	printf("[Go to Around (%d)]\n", AroundCount);
	printf("\n");

	for (int i = 0; i < ContainerCount; i++)
	{
		int j;

		if (i == ContainerCount - 1)
		{
			j = 0;
		}
		else
		{
			j = i + 1;
		}

		int selfIndex = ContainerValidIndices[i];
		int targetindex = ContainerValidIndices[j];

		Unit* selfIUnitPtr = Find_Monster(selfIndex);
		Unit* targetUnitPtr = Find_Monster(targetindex);

		if (selfIUnitPtr == nullptr || targetUnitPtr == nullptr)
			continue;

		// EndGame
		if (selfIndex == targetindex && !bIsEndFlag)
		{
			bIsEndFlag = true;

			printf("\n-------------------------------------------\n");
			printf("[Mission Complete]\n");

			printf("\n%-15s: %s\n", "Winner", selfIUnitPtr->Unit_Monster->Get_Name());
			printf("\n%-15s: %d\n", "AroundCount", AroundCount);
			printf("\n-------------------------------------------\n");
			printf("\n");

			break;
		}

		printf("-Turn %d-\n", i);
		selfIUnitPtr->Unit_Monster->Send_Damage(targetUnitPtr->Unit_Monster);
		printf("\n");

		if (!Check_Monster_IsAlive(targetindex))
		{
			Delete_Monster(targetindex);
		}
	}

	printf("\n[End to Around (%d)]", AroundCount);
	printf("\n===========================================\n");
	printf("\n");

	if (!bIsEndFlag)
	{
		AroundCount++;
	}
	else
	{
		AroundCount = 0;
	}

	return;
}

void Arena::StartGame()
{
	printf("\n###########################################\n");
	printf("\n[START GAME]\n");
	printf("\n");

	while (!bIsEndFlag)
	{
		GoToAround();
	}

	printf("\n[END GAME]\n");
	printf("\n###########################################\n");
	printf("\n");
}

void Arena::Print_Container_Ptr()
{
	if (ContainerStart == nullptr)
	{
		printf("%-15s: %p\n", "ContainerPtr", ContainerStart);
	}
	else
	{
		printf("%-15s: %p\n", "ContainerPtr", ContainerStart);
	}
}

void Arena::Print_Container_Size()
{
	printf("%-15s: %lld\n", "ContainerSize", ContainerSize);
}

void Arena::Print_Container_Count()
{
	printf("\n-------------------------------------------\n");
	printf("[Container Count]\n");
	printf("%-15s: %d\n", "ContainerCount", ContainerCount);
	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::Print_Container_Member()
{
	if (!Check_Container_IsValid())
		return;

	printf("\n-------------------------------------------\n");
	printf("[Container Member]\n");
	printf("%-15s: %d\n", "ContainerMembers", ContainerCount);
	printf("\n");

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		if (temp->Unit_Index != -1 && temp->Unit_Monster != nullptr)
		{
			printf("-Unit %d-\n", i);
			printf("%-15s: %d\n", "UnitIndex", temp->Unit_Index);
			temp->Unit_Monster->Print_Name();
			temp->Unit_Monster->Print_HealthPoint();
			printf("\n");
		}
	}

	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::Print_Unit_Ptr(Unit* InUnit)
{
	if (InUnit == nullptr)
	{
		printf("%-15s: %s\n", "UnitPtr", "nullptr");
	}
	else
	{
		printf("%-15s: %p\n", "UnitPtr", InUnit);
	}
}

void Arena::Print_Unit_MonsterPtr(Unit* InUnit)
{
	if (InUnit->Unit_Monster == nullptr)
	{
		printf("%-15s: %p\n", "UnitMonsterPtr", InUnit->Unit_Monster);
	}
	else
	{
		printf("%-15s: %p\n", "UnitMonsterPtr", InUnit->Unit_Monster);
	}
}

void Arena::Print_Unit_Index(Unit* InUnit)
{
	if (InUnit->Unit_Index == -1)
	{
		printf("%-15s: %d\n", "UnitIndex", InUnit->Unit_Index);
	}
	else
	{
		printf("%-15s: %d\n", "UnitIndex", InUnit->Unit_Index);
	}
}

void Arena::Print_Unit_MonsterName(Unit* InUnit)
{
	if (InUnit->Unit_Monster == nullptr)
	{
		printf("%-15s: %s\n", "Name", "NULL");
	}
	else
	{
		InUnit->Unit_Monster->Print_Name();
	}
}

void Arena::Print_Monster_highestHP()
{
	if (!Check_Container_IsValid())
		return;

	printf("\n-------------------------------------------\n");
	printf("[HIGHEST HP]\n");

	float mostHP = FLT_MIN;
	Monster* mostHP_monster = nullptr;

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		if (temp->Unit_Index != -1 && temp->Unit_Monster != nullptr)
		{
			float tempHP = temp->Unit_Monster->Get_HealthPoint();

			if (mostHP < tempHP)
			{
				mostHP = tempHP;
				mostHP_monster = temp->Unit_Monster;
			}
		}
	}

	if (mostHP != FLT_MIN && mostHP_monster != nullptr)
	{
		mostHP_monster->Print_Name();
		mostHP_monster->Print_HealthPoint();
	}
	else
	{
		printf("\n[Message] Find_Fail [ALL]\n");
	}

	printf("\n-------------------------------------------\n");
	printf("\n");
}

void Arena::Print_Monster_StatusData(int InUnitIndex)
{
	if (!Check_Container_IsValid())
		return;

	Unit* temp = Find_Monster(InUnitIndex);

	if (temp != nullptr)
	{
		temp->Unit_Monster->Print_StatusData();
		printf("\n");
	}
	else // temp == nullptr
	{
		printf("\n[Message] Find_Fail [UnitIndex: %d]\n", InUnitIndex);
	}
}

void Arena::Print_Monster_StatusData(const char* InName, uint64_t InSize)
{
	if (!Check_Container_IsValid())
		return;

	Unit* temp = Find_Monster(InName, InSize);

	if (temp != nullptr)
	{
		temp->Unit_Monster->Print_StatusData();
		printf("\n");
	}
	else // temp == nullptr
	{
		printf("\n[Message] Find_Fail [InName: %s]\n", InName);
	}
}

void Arena::Add_ValidIndex(int InUnitIndex)
{
	ContainerValidIndices[ContainerCount] = InUnitIndex;
	++ContainerCount;
}

void Arena::Delete_ValidIndex(int InUnitIndex)
{
	int* temp = new int[ContainerSize];
	int tempcount = 0;

	for (int i = 0; i < ContainerSize; i++)
	{
		if (ContainerValidIndices[i] != -1 && ContainerValidIndices[i] != InUnitIndex)
		{
			temp[tempcount] = ContainerValidIndices[i];
			++tempcount;
		}
	}

	for (int j = tempcount; j < ContainerSize; j++)
	{
		temp[j] = -1;
	}

	delete ContainerValidIndices;

	ContainerValidIndices = temp;
	ContainerCount = tempcount;
}

Unit* Arena::Find_Monster(int InUnitIndex)
{
	if (!Check_Container_IsValid())
		return nullptr;

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		if (temp->Unit_Index != -1 && temp->Unit_Monster != nullptr && temp->Unit_Index == InUnitIndex)
			return temp;
	}

	return nullptr;
}

Unit* Arena::Find_Monster(const char* InName, uint64_t InSize)
{
	if (!Check_Container_IsValid())
		return nullptr;

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		if (temp->Unit_Index != -1 && temp->Unit_Monster != nullptr && temp->Unit_Monster->Query_IsEqualName(InName, InSize))
			return temp;
	}

	return nullptr;
}

bool Arena::Check_Container_IsValid()
{
	return ContainerStart != nullptr && ContainerSize > 0 && ContainerValidIndices != nullptr && ContainerCount != 0 ? true : false;
}

bool Arena::Check_Monster_IsAlive(int InUnitIndex)
{
	Unit* unitPtr = Find_Monster(InUnitIndex);
	if (!unitPtr) return false;

	return unitPtr->Unit_Monster->Get_HealthPoint() > 0.f ? true : false;
}

bool Arena::Check_Monster_IsAlive(const char* InName, uint64_t InSize)
{
	Unit* unitPtr = Find_Monster(InName, InSize);
	if (!unitPtr) return false;

	return unitPtr->Unit_Monster->Get_HealthPoint() > 0.f ? true : false;
}
