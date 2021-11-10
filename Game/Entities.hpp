#pragma once
#include <iostream>
using std::string;
class Entities
{
protected:
	int m_health;
	int m_strength;
	string m_name;
	bool m_dead;
public:
	Entities();
	Entities(int h, int s, string n, bool d);
};

