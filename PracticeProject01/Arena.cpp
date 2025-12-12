#include <iostream>
#include "Arena.h"
#include "Monster.h"

Arena::Arena()
{
}

Arena::~Arena()
{
	delete ContainerValidIndices;
	delete ContainerStart;
}

void Arena::Initialize(int InContainerSize)
{
	printf("=Initialize=====\n");

	bIsEndGame = false;

	ContainerStart = new Unit[InContainerSize];
	ContainerValidIndices = new int[InContainerSize];

	ContainerSize = InContainerSize;
	ContainerCount = 0;

	printf("ContainerStart: %p\n", ContainerStart);
	printf("ContainerSize: %d\n", ContainerSize);
	printf("----------------\n");

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		temp->Unit_Monster = nullptr;
		temp->Unit_Index = -1;

		ContainerValidIndices[i] = -1;

		// printf("i: %d\n", i);
		// printf("temp: %p\n", temp);
		// printf("temp->Unit_Monster: %p\n", temp->Unit_Monster);
		// printf("temp->Unit_Index: %d\n", temp->Unit_Index);
		// printf("----------------\n");
	}

	printf("\n");
}

void Arena::Add_Monster(StatusData InStatusData)
{
	printf("=Add_Monster====\n");

	Monster* monster = new Monster;

	monster->Initialize(InStatusData);

	for (int i = 0; i < ContainerSize; i++)
	{
		Unit* temp = ContainerStart + i;

		// printf("i: %d\n", i);
		// printf("temp: %p\n", temp);
		// printf("temp->Unit_Monster: %p\n", temp->Unit_Monster);
		// printf("temp->Unit_Index: %d\n", temp->Unit_Index);
		// printf("----------------\n");

		if (temp->Unit_Index == -1)
		{
			temp->Unit_Monster = monster;
			temp->Unit_Index = i;

			Add_ValidIndex(i);

			printf("-Add_Units------\n");
			temp->Unit_Monster->Print_Name();
			printf("i: %d\n", i);
			printf("ContainerPointer: %p\n", temp);
			printf("Unit_MonsterPointer: %p\n", temp->Unit_Monster);
			printf("Unit_Number: %d\n", temp->Unit_Index);
			printf("----------------\n");

			break;
		}
	}

	printf("\n");
}

void Arena::Delete_Monster(int InUnitIndex)
{
	printf("=Delete_Monster=\n");

	Unit* temp = Find_Monster(InUnitIndex);

	printf("-Before_Delete_Units-\n");
	temp->Unit_Monster->Print_Name();
	printf("ContainerPointer: %p\n", temp);
	printf("Unit_MonsterPointer: %p\n", temp->Unit_Monster);
	printf("Unit_Number: %d\n", temp->Unit_Index);
	printf("---------------------\n");

	delete temp->Unit_Monster;

	temp->Unit_Monster = nullptr;
	temp->Unit_Index = -1;

	Delete_ValidIndex(InUnitIndex);

	printf("-After_Delete_Units--\n");
	temp->Unit_Monster->Print_Name(); // NOTICE : Implicit Work
	printf("ContainerPointer: %p\n", temp);
	printf("Unit_MonsterPointer: %p\n", temp->Unit_Monster);
	printf("Unit_Number: %d\n", temp->Unit_Index);
	printf("---------------------\n");
}

void Arena::GoToAround()
{
	if (bIsEndGame) return;

	printf("=GoToAround=====\n");

	if (!Check_Container_IsValid())
		return;

	for (int i = 0; i < ContainerCount; i++)
	{
		int idx;

		if (i == ContainerCount - 1)
		{
			idx = 0;
		}
		else
		{
			idx = i + 1;
		}

		int selfIndex = ContainerValidIndices[i];
		int targetindex = ContainerValidIndices[idx];



		// printf("i: %d\n", i);
		// printf("selfIndex: %d\n", selfIndex);
		// 
		// printf("i: %d\n", i + 1);
		// printf("targetindex: %d\n", targetindex);

		Unit* selfIUnitPtr = Find_Monster(selfIndex);
		Unit* targetUnitPtr = Find_Monster(targetindex);

		if (selfIUnitPtr == nullptr || targetUnitPtr == nullptr)
			continue;

		// selfIUnitPtr->Unit_Monster->Print_Name();
		// targetUnitPtr->Unit_Monster->Print_Name();

		if (selfIndex == targetindex)
		{
			bIsEndGame = true;

			printf("\n==MissionComplete==\n");
			printf("\nWinner: %s\n", selfIUnitPtr->Unit_Monster->Get_Name());
			printf("\n===================\n");
			break;
		}

		selfIUnitPtr->Unit_Monster->Send_Damage(targetUnitPtr->Unit_Monster);
		printf("\n");

		if (!Check_Monster_IsAlive(targetindex))
		{
			Delete_Monster(targetindex);
		}
	}
}

void Arena::StartGame()
{
	while (!bIsEndGame)
	{
		GoToAround();
	}
}

void Arena::Print_ContainerCount()
{
	printf("=Monster_Count==\n");
	printf("MonsterCount: %d\n", ContainerCount);
	printf("\n");
}

void Arena::Print_Monster_highestHP()
{
	if (!Check_Container_IsValid())
		return;

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
		printf("=Monster_HighestHP=\n");
		mostHP_monster->Print_Name();
		mostHP_monster->Print_HealthPoint();
		printf("\n");
	}
	else
	{
		printf("=Monster_StatusData=\n");
		printf("Find_Fail\n");
		printf("\n");
	}
}

void Arena::Print_Monster_StatusData(const char* InName, uint64_t InSize)
{
	if (!Check_Container_IsValid())
		return;

	Unit* temp = Find_Monster(InName, InSize);

	if (temp != nullptr)
	{
		printf("=Monster_StatusData=\n");
		temp->Unit_Monster->Print_StatusData();
		printf("\n");
	}
	else // temp == nullptr
	{
		printf("=Monster_StatusData=\n");
		printf("Find_Fail: %s\n", InName);
		printf("\n");
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
