#include <iostream>
#include "Arena.h"
#include "Monster.h"

Arena::Arena()
{
}

void Arena::Initialize(int InContainerCount)
{
	printf("=Initialize=====\n");
	ContainerStart = new Unit[InContainerCount];
	ContainerSize = InContainerCount;
	ContainerOffset = sizeof(Unit);

	printf("ContainerStart: %p\n", ContainerStart);
	printf("ContainerSize: %d\n", ContainerSize);
	printf("ContainerOffset: %d\n", ContainerOffset);
	printf("----------------\n");

	for (int i = 0; i < ContainerSize; ++i)
	{
		Unit* temp = ContainerStart + i;
		
		temp->Unit_Monster = nullptr;
		temp->Unit_Number = -1;

		// printf("i: %d\n", i);
		// printf("temp: %p\n", temp);
		// printf("temp->Unit_Monster: %p\n", temp->Unit_Monster);
		// printf("temp->Unit_Number: %d\n", temp->Unit_Number);
		// printf("----------------\n");
	}
}

void Arena::Add_Monster(StatusData InStatusData)
{
	printf("=Add_Monster====\n");

	Monster* monster = new Monster;
	
	monster->initialize(InStatusData);
	monster->PrintStatusData();

	for (int i = 0; i < ContainerSize; ++i)
	{
		Unit* temp = ContainerStart + i;

		// printf("i: %d\n", i);
		// printf("temp: %p\n", temp);
		// printf("temp->Unit_Monster: %p\n", temp->Unit_Monster);
		// printf("temp->Unit_Number: %d\n", temp->Unit_Number);
		// printf("----------------\n");

		if (temp->Unit_Number == -1)
		{
			temp->Unit_Monster = monster;
			temp->Unit_Number = i;
			
			printf("-Add_Units------\n");
			printf("i: %d\n", i);
			printf("temp: %p\n", temp);
			printf("temp->Unit_Monster: %p\n", temp->Unit_Monster);
			printf("temp->Unit_Number: %d\n", temp->Unit_Number);
			printf("----------------\n");

			break;
		}
	}
}
