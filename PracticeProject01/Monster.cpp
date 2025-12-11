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
}

void Monster::Set_Name(const char* InName)
{
	if (sizeof(InName) > MAX_NAME_LENGTH - 1)
	{
		printf("InName Length is too long (max: %d)\n", MAX_NAME_LENGTH - 1);
		return;
	}

	int i = 0;

	for (i = 0; i < sizeof(InName); i++)
	{
		Name[i] = InName[i];
		// printf("InName(%d): %c\n",i, InName[i]);
	}

	if (i <= MAX_NAME_LENGTH)
		Name[i] = '\0';

	// printf("Name:%s\n", Name);
}

void Monster::Set_Attribute(Attribute InAttribute)
{
	atrribute = InAttribute;
}

void Monster::Set_Attribute(int InNumber)
{
	if (InNumber >= Max)
	{
		printf("InNumber is not Mapping to Attribute\n");
	}

	atrribute = (Attribute)InNumber;
}

void Monster::SendDamage(Monster* InTarget)
{
	if (InTarget == nullptr)
	{
		printf("InTarget is Invalid\n");
		return;
	}

	InTarget->TakeDamage(CalculateDamage(InTarget));
}

void Monster::TakeDamage(float InDamagePoint)
{
	if (Lifepoint < 0.f)
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

float Monster::CalculateDamage(Monster* InTarget)
{
	if (InTarget == nullptr)
	{
		printf("InTarget is Invalid\n");
		return 0.f;
	}

	// BasicDamage
	float damage = this->Attack - InTarget->Get_Defense();

	// Attribute
	damage *= CalculateAtrribute(this->atrribute, InTarget->Get_Atrribute());

	// Truncate
	damage = floor(damage);

	// MinDamage
	if (damage < 1.f)
		damage = 1.f;

	printf("Damage: %f\n", damage);

	return damage;
}

float Monster::CalculateAtrribute(Attribute InMyAtrribute, Attribute InTargetAtrribute)
{
	if (InMyAtrribute == InTargetAtrribute)
		return 1.0f;

	switch (InMyAtrribute)
	{
	case Attribute::Fire:
	{
		// Attribute Type
		if (InTargetAtrribute == Attribute::Wind)
			return 1.5f;

		// Anti-Attribute Type
		else if (InTargetAtrribute == Attribute::Water || InTargetAtrribute == Attribute::Earth)
			return 0.5f;

		// Non-Attribute Type
		else
			return 1.0f;

		break; // SafeFactor
	}

	case Attribute::Water:
	{
		if (InTargetAtrribute == Attribute::Fire)
			return 1.5f;

		else if (InTargetAtrribute == Attribute::Wind)
			return 0.5f;

		else
			return 1.0f;

		break;
	}

	case Attribute::Earth:
	{
		if (InTargetAtrribute == Attribute::Water)
			return 1.5f;

		else if (InTargetAtrribute == Attribute::Wind)
			return 0.5f;

		else
			return 1.0f;

		break;
	}

	case Attribute::Wind:
	{
		if (InTargetAtrribute == Attribute::Water || InTargetAtrribute == Attribute::Earth)
			return 1.5f;

		else if (InTargetAtrribute == Attribute::Wind)
			return 0.5f;

		else
			return 1.0f;

		break;
	}

	default:
		break;
	}

	return 0.0f;
}