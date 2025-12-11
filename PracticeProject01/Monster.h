#pragma once

enum Attribute
{
	Fire = 0,
	Water,
	Earth,
	Wind,
};

class Monster
{
public:
	Monster();

private:
	float Lifepoint;
	float Attack;
	float Defense;
	Attribute atrribute;

private:
	void initialize();

public:
	float Get_Lifepoint() { return Lifepoint; }

public:
	bool Query_IsAlive() { return Lifepoint > 0.f; }

public:
	void SendDamage(Monster* InTarget);
	void TakeDamage(float InDamagePoint);
};