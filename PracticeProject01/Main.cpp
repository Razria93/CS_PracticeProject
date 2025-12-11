#include "Monster.h"
#include <iostream>

int main()
{
	Monster* monster0 = new Monster;
	Monster* monster1 = new Monster;
	
	printf("monster0.Lifepoint: %f\n", monster0->Get_Lifepoint());
	printf("monster1.Lifepoint: %f\n", monster1->Get_Lifepoint());
	printf("---\n");

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