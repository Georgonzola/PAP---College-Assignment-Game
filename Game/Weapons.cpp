#include "Weapons.hpp"

Weapons::Weapons()
{
	m_damage = 0;
	m_ID = 0;
	m_name = "NoName";
}

Weapons::Weapons(int d, int ID, string n)
{
	m_damage = d;
	m_ID = ID;
	m_name = n;
}

int Weapons::GetDamage(){return m_damage;}
