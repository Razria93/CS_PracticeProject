#include <iostream>
#include "Monster.h"
#include "Arena.h"

int main()
{
	Arena* arena = new Arena;
	arena->Initialize(10);

	StatusData statusData0 = StatusData{ "MONSTER0", sizeof("MONSTER0"),100.f, 15.f, 5.f, Attribute::Earth };
	StatusData statusData1 = StatusData{ "MONSTER1", sizeof("MONSTER1"), 50.f, 30.f, 10.f, Attribute::Water };
	StatusData statusData2 = StatusData{ "MONSTER2", sizeof("MONSTER2"), 80.f, 20.f, 5.f, Attribute::Fire };
	
	arena->Add_Monster(statusData0);
	arena->Add_Monster(statusData1);
	arena->Add_Monster(statusData2);

	return 0;
}