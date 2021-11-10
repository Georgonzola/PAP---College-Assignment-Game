#pragma once
#include "Items.hpp"
#include "Weapons.hpp"
#include "Player.hpp"
#include <random>


class Location
{
protected:
	int m_ID;
	int m_x;
	int m_y;
	bool m_Sfloor;
	const int m_map[7][4][2] =
	{
	{{'X','X'}, {101,201}, {102,'X'}, {103,'X'}},
	{{'X',210}, {'X',211}, {112,212}, {'X',213}},
	{{'X',220}, {'X',221}, {122,'X'}, {123,223}},
	{{130,230}, {131,231}, {132,232}, {133,'X'}},
	{{140,'X'}, {141,241}, {142,242}, {143,243}},
	{{150,250}, {151,'X'}, {152,252}, {153,253}},
	{{'X',260}, {161,'X'}, {'X',262}, {'X',263}},
	};

	int m_compMap[7][4][2] =
	{
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
		{{0,0}, {0,0}, {0,0}, {0,0}},
	};

public:
	Location();
	Location(int ID, int x, int y, bool f);
	void MovePlayer(char d, Items& i, Player& p);
	void DisplayLocation();
	void SwitchFloor();
	int GetID();
	void RoomCheck(Items& i, Player& p);
	void RunSpecialRoom(Items& i, Player& p);
	void RunFloor(Items& i, Player& p);
	void RunKeyItem(Items& i);
	void RunProgression(Items& i, Player& p);
	void RunScavenge(Items& i);
	void RunGeneral(Items& i);
	void SetID();
	void RunFight(Items& i, Player& p, Enemy& e);
	int FightInput(Items& i, Player& p);
	void Shop(Items& i, Player &p);
	void Workshop(Items& i);
	bool GetCompMap();
	void Finale(Items &i, Player &p);
};
