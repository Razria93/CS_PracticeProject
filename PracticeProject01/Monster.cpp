#include "Monster.h"
#include <iostream>

Monster::Monster()
{
}

void Monster::initialize(StatusData InStatusData)
{
	Set_Name(InStatusData.Name, InStatusData.NameSize);
	Set_Lifepoint(InStatusData.Lifepoint);
	Set_Attack(InStatusData.Attack);
	Set_Defense(InStatusData.Defense);
	Set_Attribute(InStatusData.Atrribute);
}

void Monster::Set_Name(const char* InName, int InSize)
{
	if (InSize > MAX_NAME_LENGTH - 1)
	{
		M_StatusData.Name[0] = '\0';

		printf("InName Length is too long (max: %d)\n", MAX_NAME_LENGTH - 1);
		printf("NameSize: %d\n", InSize);

		return;
	}

	int i = 0;

	for (i = 0; i < InSize; i++)
	{
		M_StatusData.Name[i] = InName[i];
		// printf("InName(%d): %c\n",i, InName[i]);
	}

	if (i <= MAX_NAME_LENGTH)
		M_StatusData.Name[i] = '\0';

	// printf("Name:%s\n", Name);
	// printf("NameSize: %d\n", InSize);
}

void Monster::Set_Lifepoint(float InLifepoint)
{
	M_StatusData.Lifepoint = InLifepoint;
}

void Monster::Set_Attack(float InAttack)
{
	M_StatusData.Attack = InAttack;
}

void Monster::Set_Defense(float InDefense)
{
	M_StatusData.Defense = InDefense;
}

void Monster::Set_Attribute(Attribute InAttribute)
{
	M_StatusData.Atrribute = InAttribute;
}

void Monster::Set_Attribute(int InNumber)
{
	if (InNumber >= Max)
	{
		printf("InNumber is not Mapping to Attribute\n");
	}

	M_StatusData.Atrribute = (Attribute)InNumber;
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
	if (M_StatusData.Lifepoint < 0.f)
	{
		printf("Not Enoungh LifePoint\n");
		return;
	}

	M_StatusData.Lifepoint -= InDamagePoint;

	if (M_StatusData.Lifepoint < 0.f)
	{
		M_StatusData.Lifepoint = 0.f;

		printf("LifePoint is zero\n");
		return;
	}
}

void Monster::PrintStatusData()
{
	printf("----------------\n");
	printf("%-10s: %s\n", "Name", M_StatusData.Name);
	printf("%-10s: %.1f\n", "Lifepoint", M_StatusData.Lifepoint);
	printf("%-10s: %.1f\n", "Attack", M_StatusData.Attack);
	printf("%-10s: %.1f\n", "Defense", M_StatusData.Defense);
	printf("%-10s: %d\n", "Atrribute", M_StatusData.Atrribute);
	printf("0: Fire / 1: Water / 2: Earth / 3: Wind\n");
	printf("----------------\n");
}

float Monster::CalculateDamage(Monster* InTarget)
{
	if (InTarget == nullptr)
	{
		printf("InTarget is Invalid\n");
		return 0.f;
	}

	// BasicDamage
	float damage = this->M_StatusData.Attack - InTarget->Get_Defense();

	// Attribute
	damage *= CalculateAtrribute(this->M_StatusData.Atrribute, InTarget->Get_Atrribute());

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