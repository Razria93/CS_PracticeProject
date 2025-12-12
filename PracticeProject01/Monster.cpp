#include "Monster.h"
#include <iostream>

Monster::Monster()
{
}

void Monster::Initialize(StatusData InStatusData)
{
	Set_Name(InStatusData.Name, InStatusData.NameSize);
	Set_HealthPoint(InStatusData.HealthPoint);
	Set_Attack(InStatusData.Attack);
	Set_Defense(InStatusData.Defense);
	Set_Attribute(InStatusData.Atrribute);
}

void Monster::Set_Name(const char* InName, uint64_t InSize)
{
	if (InName[InSize - 1] != '\0')
	{
		printf("InName is not null-terminated\n");
	}

	if (InSize > MAX_NAME_LENGTH)
	{
		M_StatusData.Name[0] = '\0';

		printf("InName Length is too long (max: %d)\n", MAX_NAME_LENGTH);
		printf("InNameSize: %lld\n", InSize);

		return;
	}

	int i;

	for (i = 0; i < InSize; i++)
	{
		M_StatusData.Name[i] = InName[i];
		// printf("InName(%d): %c\n",i, InName[i]);
	}

	M_StatusData.NameSize = i;
	// printf("Name:%s\n", Name);
	// printf("NameSize: %lld\n", InSize);
}

void Monster::Set_HealthPoint(float InHealthPoint)
{
	M_StatusData.HealthPoint = InHealthPoint;
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

bool Monster::Query_IsAlive()
{
	return M_StatusData.HealthPoint > 0.f;
}

bool Monster::Query_IsEqualName(const char* InName, uint64_t InSize)
{
	if (M_StatusData.NameSize != InSize)
	{
		Print_NameSize();
		printf("InNameSize: %lld\n", InSize);
		return false;
	}

	for (int i = 0; i < M_StatusData.NameSize; i++)
	{
		if (M_StatusData.Name[i] != InName[i])
			return false;
	}

	return true;
}

void Monster::Send_Damage(Monster* InTarget)
{
	if (InTarget == nullptr)
	{
		printf("InTarget is Invalid\n");
		return;
	}
	printf("Send: %s / Take: %s\n", Get_Name(), InTarget->Get_Name());
	
	InTarget->Take_Damage(CalculateDamage(InTarget));
}

void Monster::Take_Damage(float InDamagePoint)
{
	if (Get_HealthPoint() < 0.f)
	{
		printf("Not Enoungh HealthPoint\n");
		return;
	}

	float before = Get_HealthPoint();

	M_StatusData.HealthPoint -= InDamagePoint;

	float after = Get_HealthPoint();

	printf("HealthPoint(%s): %f -> %f\n", Get_Name(), before, after);

	if (Get_HealthPoint() < 0.f)
	{
		M_StatusData.HealthPoint = 0.f;

		printf("HealthPoint is zero\n");
		return;
	}
}

void Monster::Print_StatusData()
{
	printf("----------------\n");
	Print_Name();
	Print_HealthPoint();
	Print_Attack();
	Print_Defense();
	Print_Attribute();
	printf("----------------\n");
}

void Monster::Print_Name()
{
	printf("%-10s: %s\n", "Name", M_StatusData.Name);
}

void Monster::Print_HealthPoint()
{
	printf("%-10s: %.1f\n", "HealthPoint", M_StatusData.HealthPoint);
}

void Monster::Print_Attack()
{
	printf("%-10s: %.1f\n", "Attack", M_StatusData.Attack);
}

void Monster::Print_Defense()
{
	printf("%-10s: %.1f\n", "Defense", M_StatusData.Defense);
}

void Monster::Print_Attribute()
{
	printf("%-10s: %d\n", "Atrribute", M_StatusData.Atrribute);
	printf("0: Fire / 1: Water / 2: Earth / 3: Wind\n");
}

void Monster::Print_NameSize()
{
	printf("NameSize: %lld\n", M_StatusData.NameSize);
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