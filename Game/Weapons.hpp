#pragma once
#include<iostream>
using std::string;

class Weapons
{
private:
	int m_damage;
	int m_ID;
	string m_name;
public:
	Weapons();
	Weapons(int d, int ID, string n);
	int GetDamage();
};

