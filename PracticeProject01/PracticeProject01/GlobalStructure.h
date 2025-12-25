#pragma once

#define MAX_NAME_LENGTH 20

typedef unsigned long long uint64_t;

class Monster;

enum Attribute
{
	Fire = 0,
	Water,
	Earth,
	Wind,
	Max,
};

enum Status
{
	Name = 0,
	NameSize,
	HealthPoint,
	Attack,
	Defense,
	Atrribute,
};

struct StatusData
{
	char  Name[MAX_NAME_LENGTH];
	uint64_t NameSize;
	float HealthPoint;
	float Attack;
	float Defense;
	Attribute Atrribute;
};

struct Unit
{
	Monster* Unit_Monster;
	int Unit_Index; // Empty: -1
};