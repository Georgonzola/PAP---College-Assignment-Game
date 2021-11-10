#pragma once
#include "Entities.hpp"
#include "Enemy.hpp"
#include "Weapons.hpp"
#include <random>
#include <chrono>


class Player : public Entities
{
private:
	int m_luck;
	bool m_complete;
public:
	Player();
	Player(int h, int s, string n, bool d, int l, bool c);
	void DisplayStats();
	int CalcAttack(Weapons a);
	void TakeDamage(int d);
	bool GetDeath();
	void CompleteGame();
	bool GetComplete();
	void LuckyCharmGet();
	void Heal(int h);
	void LevelUp();
	int GetHealth();
};

