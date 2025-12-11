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

class Monster
{
public:
	Monster();

private:
	char  Name[MAX_NAME_LENGTH];
	float Lifepoint;
	float Attack;
	float Defense;
	Attribute atrribute;

private:
	void initialize();

public:
	void Set_Name(const char* InName);
	void Set_Attribute(Attribute InAttribute);
	void Set_Attribute(int InNumber);

public:
	char* Get_Name() { return Name; }
	float Get_Lifepoint() { return Lifepoint; }
	float Get_Attack() { return Attack; }
	float Get_Defense() { return Defense; }
	Attribute Get_Atrribute() { return atrribute; }

public:
	bool Query_IsAlive() { return Lifepoint > 0.f; }

public:
	void SendDamage(Monster* InTarget);
	void TakeDamage(float InDamagePoint);

private:
	float CalculateDamage(Monster* InTarget);
	float CalculateAtrribute(Attribute InMyAtrribute, Attribute InTargetAtrribute);
};