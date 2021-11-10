#include "Enemy.hpp"
#include <iostream>
#include <chrono>
#include <random>

#define random(min, max) rand() % (max + 1 - min) + min
using std::cout;
Enemy::Enemy()
{
	m_health = 0;
	m_strength = 0;
	m_name = "NoName";
	m_dead = 0;
	m_ID = 0;
	m_max = 0;
}

Enemy::Enemy(int h, int s, string n, bool d, int id, int m)
{
	m_health = h;
	m_strength = s;
	m_name = n;
	m_dead = d;
	m_ID = id;
	m_max = m;
}

int Enemy::CalcAttack()
{
	srand((unsigned)time(0));
	int num1 = m_strength, num2 = m_max;
	int damage = random(num1, num2);

	cout << "\nThe enemy dealt " << damage << " damage!\n";
	return damage;
}

void Enemy::TakeDamage(int d)
{
	m_health -= d;
	if (m_health <= 0)
		m_dead = true;
	else
		cout << "\nEnemy has " << m_health << " health remaining\n";
}

bool Enemy::GetDeath(){	return m_dead;}



