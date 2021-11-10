#include "Location.hpp"

#include <iostream>
#include <chrono>
#include <random>
#include <Windows.h>

#include "Weapons.hpp"
#include "Enemy.hpp"


bool movement;
using std::cout;
using std::cin;

Location::Location()
{
	m_ID = 0;
	m_x = 0;
	m_y = 0;
	m_Sfloor = 0;
}

Location::Location(int ID, int x, int y, bool f)
{
	m_ID = ID;
	m_x = x;
	m_y = y;
	m_Sfloor = f;
}


void Location::DisplayLocation()
{
	system("CLS");
	cout << "\nYou are in room " << m_ID;
	if (m_Sfloor == false)
		cout << "\nYou are on the first floor.\n";
	else
		cout << "\nYou are on the second floor.\n";
	cout << "\nFirst Floor:			Second Floor:\n"
			"       _____ _____ _____ 	       _____  \n"
			" #####| 101 | 102 | 103 |	 #####| 201 |###########\n"
			" #####|_____|_____|_____|	 _____|_____|_____ _____\n"
			" ###########| 112 |##### 	| 210 | 211 | 212 | 213 |\n"
			" ###########|_____|_____ 	|_____|_____|_____|_____|\n"
			" ###########| 122 | 123 |	| 220 | 221 |#####| 223 |\n"
			" _____ _____|_____|_____|	|_____|_____|_____|_____|\n"
			"| 130 | 131 | 132 | 133 |	| 230 | 231 | 232 |#####\n"
			"|_____|_____|_____|_____|	|_____|_____|_____|_____\n"
			"| 140 | 141 | 142 | 143 |	 #####| 241 | 242 | 243 |\n"
			"|_____|_____|_____|_____|	 _____|_____|_____|_____|\n"
			"| 150 | 151 | 152 | 153 |	| 250 |#####| 252 | 253 |\n"
			"|_____|_____|_____|_____|	|_____|#####|_____|_____|\n"
			" #####| 161 |###########	| 260 |#####| 262 | 263 |\n"
			" #####|_____|###########	|_____|     |_____|_____|\n";
	cout << "\nThere are some notes on the map:\n"
		"\n'There's a weird hole in the south-west part of the first floor's ceiling\n"
		"Should we tell management about this? - Bob'"
		"\n\n'Someone seriously needs to fix the hardrail on the stairs at 130\n"
		"Somebody is going to get hurt if we don't' - Cob"
	"\n\n'WARNING do NOT go near the wall at the south-west section of the second floor\n"
		"The wall is crumbling to pieces and will collapse at the slightest push' - Job\n";
}

void Location::SwitchFloor()
{
	if (m_Sfloor == false)
	{
		m_Sfloor = true;
		SetID();
	}
	else
	{
		m_Sfloor = false;
		SetID();
	}
}

int Location::GetID(){return m_ID;}

void Location::SetID()
{
	m_ID = m_map[m_y][m_x][m_Sfloor];
}

void Location::MovePlayer(char d, Items &i, Player &p)
{

		switch (d)
		{
		case 'w': case 'W':
			if ((m_y - 1) < 0 || (m_map[m_y - 1][m_x][m_Sfloor] == 'X'))
				cout << "\nYou run head-first into a wall.\n";
			else
			{
				if ((m_ID == 112) && (m_compMap[m_y][m_x][m_Sfloor] == 0))
				{
					cout << "\nYou can't go this way yet, you need to unlock the door\n";
					break;
				}
				else
				{
					m_y--;
					SetID();
					movement = true;
				}
			}
			break;
		case 'a': case 'A':
			if ((m_x - 1) < 0 || (m_map[m_y][m_x - 1][m_Sfloor] == 'X'))
				cout << "\nYou run head-first into a wall.\n";
			else
			{
				m_x--;
				SetID();
				movement = true;
			}
			break;
		case 's': case 'S':
			if ((m_y + 1) > 6 || (m_map[m_y + 1][m_x][m_Sfloor] == 'X'))
				cout << "\nYou run head-first into a wall\n";
			else
			{
				m_y++;
				SetID();
				movement = true;
			}
			break;
		case'd': case 'D':
			if ((m_x + 1) > 3 || (m_map[m_y][m_x + 1][m_Sfloor] == 'X'))
				cout << "\nYou run head-first into a wall.\n";
			else
			{
				if ((m_ID == 212) && (m_compMap[m_y][m_x][m_Sfloor] == 0))
					cout << "\nYou can't go this way yet, you need to unlock the door\n";
				else
				{
					m_x++;
					SetID();
					movement = true;
				}
			}
			break;

		}
		if (movement == true)
		{
			p.Heal(5);
			movement = false;
			RoomCheck(i, p);
		}
}


void Location::RoomCheck(Items &i, Player &p)
{
	switch (m_ID)
	{
	case 130: case 230: case 150: case 250: case 152: case 252:
		RunFloor(i, p);
		break;
		//floor change
	case 123: case 201:	case 103: case 161:
		RunSpecialRoom(i, p);
		break;
		// specific rooms
	case 221: case 153:
		RunScavenge(i);
		break;
		//specific scavenge
	case 112: case 212: case 242: case 263: case 101: case 223:
		RunProgression(i, p);
		break;
		//progression event
	case 213: case 253: case 260: case 210: case 141: case 143:
		RunKeyItem(i);
		break;
		//key items
	default:
		RunGeneral(i);
		break;
		//general rooms
	}
}


void Location::RunFloor(Items &i,  Player& p)
{
	system("CLS");
	switch (m_ID)
	{
	case 150: case 152:
		cout << "\nThere is a hole in the ceiling\n";
		if (i.KeyItemCheck(7) == true)
			cout << "\nYou can use your grappling hook to go through it\n";
		else
			cout << "\nYou have no way of getting through it for now\n";
		break;
	case 250: case 252:
		cout << "\nThere is a hole in the floor\n";
		if (i.KeyItemCheck(7) == true)
			cout << "\nYou can use your grappling hook to go down it safely\n";
		else
			cout << "\nYou have no way of getting through it right now\nNot without breaking some bones\n";
		break;
	case 130:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nThere is a zombie guarding the stairs to the second floor\n";
			if (i.KeyItemCheck(3) == true)
			{
				cout << "\nNow that you have a gun, you can finally fight the zombie\n"
					"\nAs you try to load the gun, the zombie notices you presence and moves in for an attack\n"
					"\nTheres no turning back now";
				Enemy StairZombie(75, 10, "Zombie", false, 3, 15);
				RunFight(i, p, StairZombie);
				if (p.GetDeath() == false)
				{
					cout << "\nThe enemy tumbles down the stairs and lands before your feet\n"
						"You nudge it to the side, finally giving you access to the upper floor\n"
						"\nYou have gained:\nLuck + 1\nStrength + 5\n\n"
						"The enemy also dropped:\n40 x Money\n5 x Scrap"
						"\n\nYou can press F to go upstairs\n";
			
					i.MoneyChange(true, 40);
					i.ScrapChange(true, 5);
					p.LevelUp();
				}
				m_compMap[m_y][m_x][m_Sfloor] = 1;
			}
			else
				cout << "The zombie has the high ground\n"
				"There is no way you can win this fight without some kind of ranged weapon\n"
				"You should walk away for now\n";
		}
		else
			cout << "\nThere is a flight of stairs in this room\n"
			"...along with the corpses of your fallen enemies\n";
		break;
	case 230:
		cout << "\nThere is a flight of stairs in this room leading down to the first floor\n";
		break;
	}
}
//COMPLETE
void Location::RunSpecialRoom(Items &i, Player &p)
{
	system("CLS");
	switch (m_ID)
	{
	case 123: case 201:
		Shop(i, p);
		break;
	case 103:
		Workshop(i);
		break;
	case 161:
		cout << "\nYou walked back into the closet\n"
			"\nThere is nothing to do here\n"
			"\nWhy are you here?\n";
		break;
	}
}
//COMPLETE

void Location::RunKeyItem(Items &i)
{
	system("CLS");
	switch (m_ID)
	{
	case 213:
		cout << "You walk into the maintenance section of the arcade";
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nYou are surprised to see several sticks of some kind of explosive laid out on the floor\n"
				"You reckon they could be useful, so you carefully place one in your bag\n";
			i.KeyItemChange(9);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou remember this as the place where you took the explosive\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;

	case 253:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nYou see a long string-like item on the floor\nAs you approach it you realise it is a fuse\n"
				"You reckon it could be useful, so you put it in your bag\n";
			i.KeyItemChange(8);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou remember this as the place where you took the fuse\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;

	case 260:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nYou see something shining in a pile of rubble to your right\nYou dig it out to see that it is an old lighter\n"
				"You reckon it could be useful, so you put it in your bag\n";
			i.KeyItemChange(10);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou remember this as the place where you took the lighter\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;

	case 210:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nIn this part of the arcade, there is one stand-out machine\n"
				"It is a slot machine that appears to be in near perfect condition\n"
				"You begin to take it apart, hoping to find something worth your time, and you do.\n"
				"A decent looking motor catches your eye\n"
				"You reckon it could be useful, so you put it in your bag\n";
			i.KeyItemChange(5);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou can see the remnants of the slot machine that you ruthlessly tore apart\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;
	case 141:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nIn this part of the arcade, there is one stand-out machine\n"
				"It is a coin pusher machine that appears to be in near perfect condition\n"
				"You begin to take it apart, hoping to find something worth your time, and you do.\n"
				"A decent looking spring catches your eye\n"
				"You reckon it could be useful, so you put it in your bag\n";
			i.KeyItemChange(2);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou can see the remnants of the coin pusher machine that you ruthlessly tore apart\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;
	case 143:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "\nIn this part of the arcade, there is one stand-out machine\n"
				"It is a laser gun game that appears to be in near perfect condition\n"
				"You begin to take it apart, hoping to find something worth your time, and you do. \n"
				"Some gun parts from the controllers are in decent condition\n"
				"You reckon they could be useful, so you put them in your bag\n";
			i.KeyItemChange(1);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "\nYou can see the remnants of the laser gun game that you ruthlessly tore apart\n"
			"There is nothing useful left here now, so you turn around to leave\n";
		break;
	}
}

void Location::RunProgression(Items &i, Player &p)
{
	system("CLS");
	switch (m_ID)
	{
	case 112:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "To your north, there is a door with the words 'Staff Only' printed on it\n"
				"You try the handle but it appears to be locked";
			if (i.KeyItemCheck(11) == true)
			{
				cout << "\n\nYou pull the slime covered key out of your bag"
					"\nIt fits perfectly in the keyhole and the door creaks open\n";
				m_compMap[m_y][m_x][m_Sfloor] = 1;
			}
			else
				cout << "\n\nYou do not have any keys you could use in this door"
				"\nYou decide to leave it be for now\n";
		}
		else
			cout << "There is an open doorway to the north, it is the entrance to the Staff Only section\n";
		break;
	case 212:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "To your east, there is a door with the words 'Maintenance' printed on it\n"
				"You try the handle but it appears to be locked";
			if (i.KeyItemCheck(12) == true)
			{
				cout << "\n\nYou pull the second key out of your bag"
					"\nIt fits perfectly in the keyhole and the door creaks open\n";
				m_compMap[m_y][m_x][m_Sfloor] = 1;
			}
			else
				cout << "\n\nYou do not have any keys you could use in this door"
				"\nYou decide to leave it be for now\n";
		}
		else
			cout << "There is an open doorway to the east, it is the entrance to the maintenance section\n";
		break;
	case 101:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "As you walk into the seemingly empty section, another slime creature drops on you from above"
				"\nYou manage to shake it off and you notice a key lodged in its body, much like the slime from the shop"
				"\nYou wonder what it's doing in the staff only section, then you notice its 'Arcade Staff' Shirt"
				"\nWhile you were busy looking at its corporate drip, the slime moves in for an attack!\n";
			Enemy KeyMonster(50, 3, "Job", false, 2, 10);
			RunFight(i, p, KeyMonster);
			if (p.GetDeath() == false)
			{
				cout << "\nThe slime crumbles to the ground, you take the key out of its corpse and put it in your bag\n"
					"\nYou have gained:\nLuck + 1\nStrength + 5\n\n"
					"The enemy also dropped:\n30 x Money\n5 x Scrap\n";
				i.MoneyChange(true, 30);
				i.ScrapChange(true, 5);
				p.LevelUp();
			}
			i.KeyItemChange(12);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "This section of the staff area is empty now,\nthere is nothing useful here anymore\n\n"
			"Only the corpse of your defeated enemy reamins\n";

		break;
	case 242:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "You approach the monster that blocks the way south\n"
				"It seems very vicious, you hope that you are stong enough to defeat it\n\n"
				"You ready yourself for battle\n";
			Enemy BarrierMonster(100, 15, "Bob", false, 4, 20);
			RunFight(i, p, BarrierMonster);
			if (p.GetDeath() == false)
			{
				cout << "\nThe enemy falls to the ground, only then do you notice the powerful looking gun strapped to its back\n"
					"Good thing it didn't use it, you take the gun and put it in your bag\n"
					"\nYou have gained:\nLuck + 1\nStrength + 5\n\n"
					"The enemy also dropped:\n50 x Money\n5 x Scrap\n";
				i.MoneyChange(true, 50);
				i.ScrapChange(true, 5);
				p.LevelUp();
			}
			i.KeyItemChange(14);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "This section of the upper floor is empty now,\nthere is nothing useful here anymore\n\n"
			"Only the corpse of your defeated enemy reamins\n";
		break;

	case 223:
		if (m_compMap[m_y][m_x][m_Sfloor] == 0)
		{
			cout << "You see a claw machine in the back corner of the maintenance area\n"
				"The lights are on and the machine seems to be in working order\n"
				"You insert a coin into the machine and guide the biggest toy into the exit chute"
				"As the toy exits the machine you realise the claw is still attached to the toy\n\n"
				"And the toy is not a toy, it is a toy-shaped monster!\n"
				"You prepare to attack\n";
			Enemy ClawMonster(85, 10, "Cob", false, 4, 15);
			RunFight(i, p, ClawMonster);
			if (p.GetDeath() == false)
			{
				cout << "\nYou rip the claw out of the toy monster's body and put it in your bag\n"
					"You also take your fair share of coins after breaking open the machine's coin compartment\n"
					"\nYou have gained:\nLuck + 1\nStrength + 5\n\n"
					"The enemy also dropped:\n60 x Money\n5 x Scrap\n";
				i.MoneyChange(true, 60);
				i.ScrapChange(true, 5);
				p.LevelUp();
			}
			i.KeyItemChange(4);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
			cout << "This section of the maintenance area is empty now,\nthere is nothing useful here anymore\n\n"
			"Only the corpse of your defeated enemy reamins\n";
		break;
	case 263:

		cout << "_|___|___|___|___|___|___|___|\n"
				"___|___|___|___|___|___|___|__\n"
				"_|___|___|___|___|___|___|___|\n"
				"___|___|___|___|___|___|___|__\n"
				"_|___|___|___|___|___|___|___|\n"
				"___|___|___|___|___|___|___|__\n"
				"_|___|___|___|___|___|___|___|\n\n";


		cout << "One of the walls in this section seems to be on its last legs\n"
			"The mass of brick and wallpaper looks like it could fall over with the slightest breeze"
			"\nYou give it a good kick just to be sure\nIt doesn't fall over"
			"\n\nYou're going to need something a bit stonger to get through";
		Sleep(2000);
		if (i.KeyItemCheck(9) == true)
		{
			cout << "\n\nYou place the explosive down in front of the wall\n";
			Sleep(2000);
			if (i.KeyItemCheck(8) == true)
			{
				cout << "\nYou roll out the fuse coil to a safe enough distance\n";
				Sleep(2000);
				if (i.KeyItemCheck(10) == true)
				{
					cout << "\nYou light the fuse and cover your ears\n";
					Sleep(1000);
					cout << ".";
					Sleep(1000);
					cout << ".";
					Sleep(1000);
					cout << ".";
					Sleep(2000);
					Finale(i, p);
				}
				else
					cout << "\nYou then realise that you have nothing to light it with\n\n"
					"You should find something that can do that\n";
			}
			else
				cout << "\nYou feel nervous standing next to the explosive\n\n"
				"You should find something that can put some distance between you two\n";
		}
		else
			cout << "\nYou don't have anything you think could knock it down yet\n\n"
			"Maybe you should keep looking around\n";
		break;
	
	}
}

void Location::RunScavenge(Items &i)
{
	system("CLS");
	if (m_ID == 221)
	{
		if (m_compMap[m_y][m_x][m_Sfloor] == false)
		{
			cout << "You find yourself in an arcade section with one stand out machine, "
				"unlike the others, this pinball machine is in decent condition\n"
				"As you take it apart, you find a store of pinballs, these could prove to be good ammunition"
				"\n\nYou have gained:\nAmmo x 10\n";
			i.AmmoChange(true, 10);
			m_compMap[m_y][m_x][m_Sfloor] = true;
		}
		else
			cout << "You have already taken apart the pinball machine here,\nthere is nothing useful to take anymore";
	}
	else
	{
		if (m_compMap[m_y][m_x][m_Sfloor] == false)
		{
			cout << "You find yourself in a snack bar in the corner of the arcade\n"
				"Most of the food items have gone off, but a few of the packaged items seem salvageable\n"
				"\n\nYou have gained:\nSnacks x 5\n";
			i.SnackChange(true, 5);
			m_compMap[m_y][m_x][m_Sfloor] = true;
		}
		else
			cout << "You have already taken anything of value from the snackbar\nThere is no reason to be in this area anymore";
	}

}

void Location::RunGeneral(Items &i)
{
	system("CLS");
	if (m_compMap[m_y][m_x][m_Sfloor] == 0)
	{
		char ans;
		cout << "\nYou are in an averge arcade section, "
			"there are some machines you can scavenge.\n";
		if ((m_ID == 241) && (i.KeyItemCheck(14) == false))

				cout << "\nThere appears to be a strong enemy to your east,\n"
				"I wouldn't recommend taking it on without a decent weapon\n";

		if ((m_ID == 232) && (i.KeyItemCheck(14) == false))
				cout << "\nThere appears to be a strong enemy to your south,\n"
				"I wouldn't recommend taking it on without a decent weapon\n";
			

		cout <<"\nPress E to search the machines for useful parts\n";
		cin >> ans;
		if ((ans == 'e') || (ans == 'E'))
		{
			cout << "\nYou rip apart the old arcade consoles, you find: \n"
				"\nMoney x 5\nScrap x 5\n\nYou put the items in your bag.\n";
			i.ScrapChange(true, 5);
			i.MoneyChange(true, 5);
			m_compMap[m_y][m_x][m_Sfloor] = 1;
		}
		else
		{
			cout << "\nYou decide to leave it be for now.\n";

		}
	}
	else
		cout << "\nYou are in an averge arcade section, "
		"you have already scrapped the machines here.\n"
		"There is nothing useful in this section.\n";
	

}
//COMPLETED



void Location::RunFight(Items &i, Player &p, Enemy &e)
{	
	bool end;
	Weapons Pipe(15, 2, "Pipe");
	Weapons BadGun(20, 3, "Bad Gun");
	Weapons Sword(25, 4, "Sword");
	Weapons BetterGun(30, 5, "Better Gun");
	do
	{
		end = false;
		int ans;
		ans = FightInput(i, p);
		switch (ans)
		{
		case 1:
			e.TakeDamage(p.CalcAttack(Pipe));
			break;
		case 2:
			e.TakeDamage(p.CalcAttack(BadGun));
			break;
		case 3:
			e.TakeDamage(p.CalcAttack(Sword));
			break;
		case 4:
			e.TakeDamage(p.CalcAttack(BetterGun));
			break;
		case 5:
			cout << "\nYou heal for 25 health\n";
		}
		if (e.GetDeath() == true)
		{
			cout << "\nThe enemy has died!\n";
			end = true;
			return;
		}
		p.TakeDamage(e.CalcAttack());
		if (p.GetDeath() == true)
			end = true;

	} while (end == false);

} 
//COMPLETED


int Location::FightInput(Items &i, Player &p)
{
	int ans = NULL;
	bool suitable = false;
	do
	{
		cout << "\nYou have "<< p.GetHealth()<< " health and "<< i.GetAmmo()<< " ammo";
		cout << "\n\nChoose your weapon!\n\n"
			"1: Pipe\n";
		if (i.KeyItemCheck(3) == true)
			cout << "2: Gun\n";
		if (i.KeyItemCheck(13) == true)
			cout << "3: Sword\n";
		if (i.KeyItemCheck(14) == true)
			cout << "4: Better Gun\n";
		cout << "5: Heal instead\n";
		cin >> ans;
		system("CLS");
		switch (ans)
		{
		case 1:
			suitable = true;
			break;
		case 2:
			if (i.KeyItemCheck(3) == true)
			{
				if (i.GetAmmo() > 0)
				{
					suitable = true;
					i.AmmoChange(false, 1);
				}
				else
					cout << "\nYou do not have any ammo you can use\n";
			}
			else
				cout << "\nInvalid Input\n";
			break;
		case 3:
			if (i.KeyItemCheck(13) == true)
				suitable = true;
			else
				cout << "\nInvalid Input\n";
			break;
		case 4:
			if (i.KeyItemCheck(14) == true)
			{
				if (i.GetAmmo() > 0)
				{
					suitable = true;
					i.AmmoChange(false, 1);
				}
				else
					cout << "\nYou do not have any ammo you can use\n";
			}
			else
				cout << "\nInvalid Input\n";
			break;
		case 5:
			if (i.GetSnack() > 0)
			{
				p.Heal(25);
				i.SnackChange(false, 1);
				suitable = true;
			}
			else
				cout << "\nYou do not have any snacks available\n";
		default:
			cout << "\nInvalid Input\n";
		}


	} while (suitable == false);
	return ans;
}
//COMPLETED


void Location::Shop(Items& i, Player &p)
{
	bool suitable = false;
	do
	{
		int ans = NULL;
		system("CLS");
		cout << "\nYou walk into a makeshift shop tucked into the corner of the floor\n";
		if (m_ID == 123)
		{
			cout << "\nYou are greeted (??) by a filthy slime-like creature who seems to own this small shop"
				"\nIt vaguely gestures towards its store of goods by twisting its gross body towards the item shelves"
				"\nAs it does, you notice a shiny object sticking our from the bottom of its head, it looks like a key"
				"\nYou presume the slime wants you to buy something, what will you buy?\n\n";

			cout << "You have "<< i.GetMoney()<< " money\n\n";

			cout << "1: Ask for some Snacks (5 money)\n";
			if (i.KeyItemCheck(15) == false)
				cout << "2: Ask for the Lucky Charm (50 money)\n";
			if (i.KeyItemCheck(11) == false)
				cout << "3: Ask for something from the back shelf\n";
			cout << "4: Nothing\n";
			cin >> ans;
			switch (ans)
			{
			case 1:
				if (i.GetMoney() >= 5)
				{
					cout << "\n\nYou bought a snack\n";
					suitable = true;
					i.SnackChange(true, 1);
					cout << "\nYou lay your coins onto the table\n"
						"The slime slams its head onto the table, "
						"absorbing the coins into its gelatinous body"
						"\n\nYou back away slowly";
					i.MoneyChange(false, 5);
				}
				else
				{
					cout << "\n\nYou do not have enough money\n";
					Sleep(1000);
				}
				break;
			case 2:
				if (i.KeyItemCheck(15) == false)
				{
					if (i.GetMoney() >= 50)
					{
						cout << "\n\nYou bought the lucky charm\n";
						suitable = true;
						i.KeyItemChange(15);
						p.LuckyCharmGet();
						cout << "\nYou lay your coins onto the table\n"
							"The slime slams its head onto the table, "
							"absorbing the coins into its gelatinous body"
							"\n\nYou back away slowly";
						i.MoneyChange(false, 50);
					}
					else
					{
						cout << "\n\nYou do not have enough money\n";
						Sleep(1000);
					}
				}
				else
				{
					cout << "\n\nInvalid Input";
					Sleep(1000);
				}
				break;

			case 3:
				if (i.KeyItemCheck(11) == false)
				{
					cout << "As the slime turns around to reach the back shelf, "
						"you yank the key out of its head\nSomehow it doesn't notice, "
						"you put the key into your pocket before it turns back around with "
						"a carpet hair covered lollipop\n\nYou politely decline\n";
					suitable = true;
					i.KeyItemChange(11);
					break;
				}
				else
				{
					cout << "\n\nInvalid Input";
					Sleep(1000);
				}
			case 4:
				cout << "You do not need anything for the time being,"
					" you wave goodbye to the slime and turn around to leave";
				suitable = true;
				break;
			default:
				suitable = false;
				cout << "\n\nInvalid Input";
				Sleep(1000);
			}
		}
		else
		{
			cout << "\nYou walk towards a boarded up wall with 'SHOP' scribbled above it in marker pen\n"
				"You pull at some of the ropes holding the boards together and peer through the gap you made\n\n"
				"'Hello?' you ask into the darkness\n\n"
				"A very nervous man edges his way towards you,"
				"\n\n'Are you a monster?' He manages to squeak out,"
				"\n\n'No.' you reply, and the man visibly breathes out a sigh of relief\n\n"
				"'So, do you want to uhhh, buy anything?'\n\n";

			cout << "You have " << i.GetMoney() << " money\n\n";

			cout << "1: Ask for some Ammo (3 x Ammo) (10 money)\n";
			if (i.KeyItemCheck(13) == false)
				cout << "2: Ask for the Sword (30 money)\n";
			if (i.KeyItemCheck(6) == false)
				cout << "3: Ask for the ropes that hold his shop together\n";
			cout << "4: Nothing\n";
			cin >> ans;
			switch (ans)
			{
			case 1:
				if (i.GetMoney() >= 10)
				{
					cout << "\n\nYou bought some ammo\n";
					suitable = true;
					i.SnackChange(true, 1);
					cout << "\nYou slot the coins inbetween the gaps of his defences\n"
						"The man pushes the box of pinballs out of another gap, "
						"\n\nYou turn around to leave";
					i.MoneyChange(false, 10);
				}
				else
				{
					cout << "\n\nYou do not have enough money\n";
					Sleep(1000);
				}
				break;
			case 2:
				if (i.KeyItemCheck(13) == false)
				{
					if (i.GetMoney() >= 50)
					{
						cout << "\n\nYou bought the Sword\n";
						suitable = true;
						i.KeyItemChange(13);
						cout << "\nYou  slot the coins inbetween the gaps of his defences\n"
							"The man tries to push the sword through the gap, "
							"it takes a while but the sword finally falls into your possesion"
							"\n\nYou turn around to leave";
						i.MoneyChange(false, 30);
					}
					else
					{
						cout << "\n\nYou do not have enough money\n";
						Sleep(1000);
					}
				}
				else
				{
					cout << "\n\nInvalid Input";
					Sleep(1000);
				}
				break;

			case 3:
				if (i.KeyItemCheck(6) == false)
				{
					cout << "'Sure, but it's gonna cost you, i'd say 60 coins'\n\n"
						"'I can afford that' you say confidently,";
					if (i.GetMoney() >= 60)
					{
						cout << "\n\nYou bought the rope\n";
						suitable = true;
						i.KeyItemChange(6);
						cout << "\nYou meticulously undo the rope keeping his defences together,"
							" making sure not to damage the rope your spent so much money on\n"
							"The wall of boards finally falls apart,"
							" only to reveal another haphazardly put together wall of boards"
							"\n\nYou let out a heavy sigh then turn around to leave";
						i.MoneyChange(false, 60);
					}
					else
					{
						Sleep(500);
						cout << "\n\n'Uhhhh actually I cant afford that'\n";
						cout << "\n'Then come back when you can'\n";
						Sleep(500);
					}
				}
				else
				{
					cout << "\n\nInvalid Input";
					Sleep(1000);
				}
				break;
			case 4:
				cout << "You do not need anything for the time being,"
					"\nyou return the boards you moved, covering up the holes and turn around to leave";
				suitable = true;
				break;
			default:
				suitable = false;
				cout << "\n\nInvalid Input";
				Sleep(1000);
			}
		}
	} while (suitable == false);

}
//COMPLETED


void Location::Workshop(Items& i)
{
	bool suitable = false;
	if ((i.KeyItemCheck(7) == true) && (i.KeyItemCheck(7) == true))
	{
		cout << "Theres nothing else that you can make here, so you leave the workbench alone";
		return;
	}
	else
	{
		do
		{
			int ans;
			system("CLS");
			cout << "You walk towards the workbench set up in the corner of the staff area, there are a few blueprints scattered acrross the table\n"
				"The drawings are quite complicated but you seem to get the jist of it\n"
				"\nWhat will you make?\n"
				"------------------------\n";
			if (i.KeyItemCheck(3) == false)
				cout << "1: Gun\n1 x Gun Parts\n1 x Spring\n20 x Scrap\n\n";
			if (i.KeyItemCheck(7) == false)
				cout << "2: Grappling hook\n1 x Claw\n1 x Motor\n1 x Rope\n25 x Scrap\n\n";
			cout << "3: Nothing\n";
			cin >> ans;
			switch (ans)
			{
			case 1:
				if ((i.KeyItemCheck(1) == true) && (i.KeyItemCheck(2) == true) && i.GetScrap() >= 20)
				{
					cout << "\nYou haphazardly put the pieces into something that vaguely resembles a gun\n"
						"It's definitely not perfect, but it'll have to do\n"
						"You find a pack of pinballs on a shelf next to the workbench, these could make good ammo\n\n"
						"You put the gun and ammo in your bag and step away from the worktable\n"
						"\n\nYou have gained: \nAmmo x 10\n";
					i.AmmoChange(true, 10);
					i.ScrapChange(false, 20);
					i.KeyItemChange(3);
					suitable = true;
				}
				else
					cout << "\nYou do not have all the required items to build this, so you leave the workbench alone";
				break;
			case 2:
				if ((i.KeyItemCheck(1) == true) && (i.KeyItemCheck(2) == true) && (i.KeyItemCheck(2) == true) && i.GetScrap() >= 25)
				{
					cout << "\nYou put the pieces together as per the blueprint ... you think\n"
						"The grappling hook looks shoddy but it seems to be able to support your weight\n\n"
						"You put the grappling hook in your bag and step away from the worktable\n";
					i.ScrapChange(false, 25);
					i.KeyItemChange(7);
					suitable = true;
				}
				else
					cout << "\nYou do not have all the required items to build this, so you leave the workbench alone";
				break;
			case 3:

				cout << "\nYou leave the worktable alone for now\n";
				suitable = true;
				break;
			default:
				cout << "\nInvalid Input";
				Sleep(1000);
			}
		} while (suitable == false);
	}
}

bool Location::GetCompMap()
{
	return m_compMap[m_y][m_x][m_Sfloor];
}

void Location::Finale(Items& i, Player& p)
{
	system("CLS");

	cout << "\n______  _____  ________  ___\n"
			"| ___ ||  _  ||  _  |  |/  |\n"
			"| |_/ /| | | || | | | .  . |\n"
			"| ___ || | | || | | | ||/| |\n"
			"| |_/ /| |_/ /| |_/ / |  | |\n"
			"|_____/|____/ |____/|_|  |_/\n\n";

	cout << "The explosion fills the room with dust\n"
		"You wait for it to clear, getting ready to venture out to freedom";
	Sleep(4000);
	system("CLS");
	Sleep(1000);
	cout << "_|___|___|___|___|___|___|___|\n"
			"___|___|___|___|___|___|___|__\n"
			"_|___|___|___|___|___|___|___|\n"
			"___|___|___|___|___|___|___|__\n"
			"_|___|___|___|___|___|___|___|\n"
			"___|___|___|___|___|___|___|__\n"
			"_|___|___|___|___|___|___|___|\n\n";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";

	cout << "\nNothing happened...\n\n";
	Sleep(2000);
	cout << "Maybe there was something you missed, some small minute detail like a tiny hole in a wall\n\n"
		"You turn around to leave but suddenly...";
	Sleep(3000);
	system("CLS");
	cout << "A GIANT HAND BURSTS THROUGH THE WALL\n\n"
		"           ___________    ____\n"
		"    ______/   \\__//   \\__/____\\\n"
		"  _/   \\_/  :           //____\\\\\n"
		" /|      :  :  ..      /       \\\n"
		"| |     ::     ::      \\       /\n"
		"| |     :|     ||     \\ \\_____/\n"
		"| |     ||     ||      |\\  /  |\n"
		" \\|     ||     ||      |   / | \\\n"
		"  |     ||     ||      |  / /_\\ \\\n"
		"  | ___ || ___ ||      | /  /    \\\n"
		"   \\_-_/  \\_-_/ | ____ |/__/      \\\n"
		"                _\\_--_/    \\      /\n"
		"               /____             /\n"
		"              /     \\           /\n"
		"              \\______\\_________/\n";
	Sleep(2000);
	cout << "\nYou hastily whip out your weapons and prepare for battle!";

	Enemy BigOleHand(100, 20, "Hob", false, 4, 30);
	RunFight(i, p, BigOleHand);
	if (p.GetDeath() == false)
	{
		p.CompleteGame();
		cout << "You did it...\n\nIts dead...";
		Sleep(1000);
		cout << "You let out a heavy breath and set down your weapons\n"
			"You're finally out of the arcade and you are blessed by an incredible skyline of your home city"
			"Though you cannot rest for long, there are bound to be more enemies in your path as work to discover what caused this strange phenomenon.";
		Sleep(1000);
	}
	else
		cout << "\nWell thats unfortunate... It is the last fight after all\n\n";
}



