#include "Monster.h"
#include <iostream>

int main()
{
	Monster* monster0 = new Monster;
	Monster* monster1 = new Monster;
	Monster* monster2 = new Monster;

	StatusData status0 = StatusData{ "MONSTER0", sizeof("MONSTER0"),100.f, 15.f, 5.f, Attribute::Earth};
	StatusData status1 = StatusData{ "MONSTER1", sizeof("MONSTER1"), 50.f, 30.f, 10.f, Attribute::Water };
	StatusData status2 = StatusData{ "MONSTER2", sizeof("MONSTER2"), 80.f, 20.f, 5.f, Attribute::Fire };

	monster0->initialize(status0);
	monster1->initialize(status1);
	monster2->initialize(status2);

	printf("\n======================\n");
	printf("\nStatus\n");
	printf("\n======================\n");
	
	monster0->PrintStatusData();
	monster1->PrintStatusData();
	monster2->PrintStatusData();

	printf("\n======================\n");
	printf("\nBattlePhase\n");
	printf("\n======================\n");

	while (true)
	{
		if (!monster0->Query_IsAlive())
		{
			delete monster0;
			monster0 = nullptr;

			printf("monster0 is LifePoint Zero\n");
			printf("monster0 is destroyed\n");
		}

		if (!monster1->Query_IsAlive())
		{
			delete monster1;
			monster1 = nullptr;

			printf("monster1 is LifePoint Zero\n");
			printf("monster1 is destroyed\n");
		}
		
		if (monster0 == nullptr || monster1 == nullptr)
		{
			printf("\n======================\n");
			printf("\nSimulation is Complete\n");
			printf("\n======================\n");
			break;
		}

		monster0->SendDamage(monster1);

		printf("monster0.Lifepoint: %f\n", monster0->Get_Lifepoint());
		printf("monster1.Lifepoint: %f\n", monster1->Get_Lifepoint());
		printf("---\n");
	}

	return 0;
}