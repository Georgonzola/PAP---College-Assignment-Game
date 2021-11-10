#include "Entities.hpp"

Entities::Entities()
{
	m_health = 0;
	m_strength = 0;
	m_name = "NoName";
	m_dead = 0;
}

Entities::Entities(int h, int s, string n, bool d)
{
	m_health = h;
	m_strength = s;
	m_name = n;
	m_dead = d;
}
