#pragma once
#include "Location.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Weapons.hpp"
#include "Items.hpp"
void UserInput(Location& i, Items& b, Player& c);

void StartFight(Player& a, Enemy& b, Weapons& c);

void OpeningText();