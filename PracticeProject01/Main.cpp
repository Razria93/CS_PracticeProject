#include <iostream>

#include "GlobalStructure.h"
#include "Monster.h"
#include "Arena.h"

int main()
{
	Arena* arena = new Arena;
	int containerSize = 10;

	arena->Initialize(containerSize);

	StatusData statusData0 = StatusData{ "MONSTER0", sizeof("MONSTER0"),100.f, 15.f, 5.f, Attribute::Earth };
	StatusData statusData1 = StatusData{ "MONSTER1", sizeof("MONSTER1"), 50.f, 30.f, 10.f, Attribute::Water };
	StatusData statusData2 = StatusData{ "MONSTER2", sizeof("MONSTER2"), 80.f, 20.f, 5.f, Attribute::Fire };
	StatusData statusData3 = StatusData{ "MONSTER3", sizeof("MONSTER3"), 20.f, 20.f, 30.f, Attribute::Wind };

	arena->Add_Monster(statusData0);
	arena->Add_Monster(statusData1);
	arena->Add_Monster(statusData2);
	arena->Add_Monster(statusData3);

	arena->Print_ContainerCount();
	arena->Print_Monster_StatusData("MONSTER0", sizeof("MONSTER0"));
	arena->Print_Monster_StatusData("MONSTER1", sizeof("MONSTER1"));
	arena->Print_Monster_StatusData("MONSTER2", sizeof("MONSTER2"));
	arena->Print_Monster_StatusData("MONSTER3", sizeof("MONSTER3"));

	arena->Print_Monster_highestHP();

	arena->Delete_Monster(0);
	arena->Print_ContainerCount();
	arena->Print_Monster_StatusData("MONSTER0", sizeof("MONSTER0"));

	// arena->GoToAround(); 

	arena->StartGame();

	return 0;
}