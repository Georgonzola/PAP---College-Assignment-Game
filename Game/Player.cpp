#include "Player.hpp"
#include<iostream>
#include <chrono>
#include <random>
#define random(min, max) rand() % (max + 1 - min) + min
using std::cout;

Player::Player()
{
	m_health = 0;
	m_strength = 0;
	m_name = "NoName";
	m_dead = 0;
	m_luck = 0;
	m_complete = false;
}

Player::Player(int h, int s, string n, bool d, int l, bool c)
{
	m_health = h;
	m_strength = s;
	m_name = n;
	m_dead = d;
	m_luck = l;
	m_complete = c;
}

void Player::DisplayStats()
{
	cout << "\nPlayer name: " << m_name;
	cout << "\n\nHealth: " << m_health;
	cout << "\nStrength: " << m_strength;
	cout << "\nLuck: " << m_luck;
	if (m_dead == 0)
		cout << "\n\nYou are alive.";
	else
		cout << "\n\nYou are dead, you shouldn't be seeing this. :/";
}

int Player::CalcAttack(Weapons a)
{
	srand((unsigned)time(0));
	int num1 = m_strength, num2 = a.GetDamage();
	int damage = random(num1, num2);

	if (m_luck * (random(1, 10)) >= 20)
	{
		damage = damage * 2;
		cout << "\nCritical Hit!\n";
	}
	cout << "\nYou dealt " << damage << " damage!\n";
	return damage;
}

void Player::TakeDamage(int d)
{
	m_health -= d;
	if (m_health <= 0)
	{
		CompleteGame();
		m_dead = true;
	}
	else
		cout << "\nYou have " << m_health << " health remaining\n";
}

bool Player::GetDeath(){return m_dead;}

void Player::CompleteGame()
{
	m_complete = true;
}

bool Player::GetComplete(){return m_complete;}

void Player::LuckyCharmGet()
{
	m_luck += 3;
}

void Player::Heal(int h)
{
	m_health += h;
	if (m_health > 100)
		m_health = 100;
}

void Player::LevelUp()
{
	m_strength += 5;
	m_luck += 1;
}

int Player::GetHealth(){return m_health;}

