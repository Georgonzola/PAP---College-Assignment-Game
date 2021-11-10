#pragma once
#include "Entities.hpp"
#include "Player.hpp"
#include <random>
#include <chrono>


class Enemy : public Entities
{
private:
	int m_ID;
	int m_max;
public:
	Enemy();
	Enemy(int h, int s, string n, bool d, int id, int m);
	void TakeDamage(int d);
	int CalcAttack();
	bool GetDeath();
};

