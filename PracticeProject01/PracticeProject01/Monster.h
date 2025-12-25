#pragma once

#include "GlobalStructure.h"

class Monster
{
public:
	Monster();
	Monster(StatusData InStatusData);

private:
	StatusData M_StatusData;

public:
	void Initialize(StatusData InStatus);

public:
	void Set_Name(const char* InName, uint64_t InSize);
	void Set_HealthPoint(float InHealthPoint);
	void Set_Attack(float InAttack);
	void Set_Defense(float InDefense);
	void Set_Attribute(Attribute InAttribute);
	void Set_Attribute(int InNumber);

public:
	char* Get_Name() { return M_StatusData.Name; }
	float Get_HealthPoint() { return M_StatusData.HealthPoint; }
	float Get_Attack() { return M_StatusData.Attack; }
	float Get_Defense() { return M_StatusData.Defense; }
	Attribute Get_Atrribute() { return M_StatusData.Atrribute; }

public:
	bool Query_IsAlive();
	bool Query_IsEqualName(const char* InName, uint64_t InSize);

public:
	void Send_Damage(Monster* InTarget);
	void Take_Damage(float InDamagePoint);

	void Print_StatusData();
	void Print_Name();
	void Print_HealthPoint();
	void Print_Attack();
	void Print_Defense();
	void Print_Attribute();
	void Print_NameSize();

private:
	float CalculateDamage(Monster* InTarget);
	float CalculateAtrribute(Attribute InMyAtrribute, Attribute InTargetAtrribute);
};