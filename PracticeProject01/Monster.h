#pragma once

#define MAX_NAME_LENGTH 20

enum Attribute
{
	Fire = 0,
	Water,
	Earth,
	Wind,
	Max,
};

struct StatusData
{
	char  Name[MAX_NAME_LENGTH];
	int   NameSize;
	float Lifepoint;
	float Attack;
	float Defense;
	Attribute Atrribute;
};

class Monster
{
public:
	Monster();

private:
	StatusData M_StatusData;

public:
	void initialize(StatusData InStatus);

public:
	void Set_Name(const char* InName, int InSize);
	void Set_Lifepoint(float InLifepoint);
	void Set_Attack(float InAttack);
	void Set_Defense(float InDefense);
	void Set_Attribute(Attribute InAttribute);
	void Set_Attribute(int InNumber);

public:
	char* Get_Name() { return M_StatusData.Name; }
	float Get_Lifepoint() { return M_StatusData.Lifepoint; }
	float Get_Attack() { return M_StatusData.Attack; }
	float Get_Defense() { return M_StatusData.Defense; }
	Attribute Get_Atrribute() { return M_StatusData.Atrribute; }

public:
	bool Query_IsAlive() { return M_StatusData.Lifepoint > 0.f; }

public:
	void SendDamage(Monster* InTarget);
	void TakeDamage(float InDamagePoint);
	void PrintStatusData();

private:
	float CalculateDamage(Monster* InTarget);
	float CalculateAtrribute(Attribute InMyAtrribute, Attribute InTargetAtrribute);
};