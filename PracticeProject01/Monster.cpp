#include "Monster.h"
#include <iostream>

Monster::Monster()
{
	initialize();
}

void Monster::initialize()
{
	Lifepoint = 50.f;
	Attack = 10.f;
	Defense = 5.f;
	atrribute = Attribute::Fire;
}

void Monster::SendDamage(Monster* InTarget)
{
	if (InTarget == nullptr)
	{
		printf("InTarget is Invalid\n");
		return;
	}

	float damage = (this->Attack) - (InTarget->Defense);

	InTarget->TakeDamage(damage);
}

void Monster::TakeDamage(float InDamagePoint)
{
	if(Lifepoint < 0.f)
	{
		printf("Not Enoungh LifePoint\n");
		return;
	}

	Lifepoint -= InDamagePoint;

	if (Lifepoint < 0.f)
	{
		Lifepoint = 0.f;

		printf("LifePoint is zero\n");
		return;
	}
}
