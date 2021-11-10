#include "Functions.hpp"
#include "Location.hpp"
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include <windows.h>

using std::cout;
using std::cin;

void UserInput(Location &i, Items &b, Player &c)
{
	bool suitable = true;
	char answer = NULL;
	do {
		cout << "\nEnter a command (press h for help)\n";
		cin >> answer;
		switch (answer)
		{
		case 'w': case 'a': case 's': case 'd': case 'W': case 'A': case 'S': case 'D':
			suitable = true;
			i.MovePlayer(answer, b, c);
			break;

		case 'm': case 'M':
			i.DisplayLocation();
			break;

		case 'f': case 'F':
			switch (i.GetID())
			{
			case 130:
				if (i.GetCompMap() == true)
				{
					cout << "\nYou go up the stairs leading to the second floor\n";
					Sleep(2000);
					i.SwitchFloor();
					suitable = true;
					i.RoomCheck(b, c);
				}
				else
					cout << "\nYou can't do that yet, you need to defeat the zombie\n";
				break;
			case 230:
				cout << "\nYou go down the stairs leading to the first floor\n";
				Sleep(2000);
				i.SwitchFloor();
				suitable = true;
				i.RoomCheck(b, c);
				break;
			case 150: case 250: case 152: case 252:
				if (b.KeyItemCheck(7) == true)
				{
					cout << "\nYou go through the hole using your grappling hook\n";
					Sleep(2000);
					i.SwitchFloor();
					suitable = true;
					i.RoomCheck(b, c);
				}
				else
					cout << "\nYou can't do that yet, you need a grappling hook\n";
				break;
			default:
				cout << "\nYou can't do that here\n";
			}
			break;

		case 'i': case 'I':
			b.DisplayInventory();
			break;
		case 'u': case 'U':
			c.DisplayStats();
			break;
		case 'l': case 'L':
			i.RoomCheck(b, c);
			break;
		case'h': case 'H':
			cout <<"\nW = North\nA = West\nS = South\nD = East\n\nM = Map\nI = Inventory\nU = Show player stats\nL = Look\n" ;
			if (i.GetID() == 130 || i.GetID() == 230 || i.GetID() == 150 || i.GetID() == 250)
				cout << "F = Change Floor\n";
			break;
		default:
			suitable = false;
		}

	} while (suitable == false);
}


void StartFight(Player &a, Enemy &b, Weapons &c)
{
	bool end = false;
	cout << "\nA battle has begun!\n\n";

	do
	{
		end = false;
		int ans = NULL;
		cout << "You have " << a.GetHealth() << " health";
		cout << "\n\nChoose your weapon!\n\n"
			"1: Mop\n";
		cin >> ans;
		if (ans == 1)
		{
			system("CLS");
			b.TakeDamage(a.CalcAttack(c));
			if (b.GetDeath() == true)
			{
				cout << "\nThe enemy has died!\n"
					"\nYou have gained:\nLuck + 1\nStrength + 5\n\n"
					"The enemy also dropped:\n10 x Money\n5 x Scrap";
				end = true;
				return;
			}
			a.TakeDamage(b.CalcAttack());
			if (a.GetDeath() == true)
			{
				cout << "\nYou died on the first fight?\nHow is that even possible?\n";
				end = true;
				exit;
			}
		}
		else
		{
			cout << "\nInvalid Input\n";
			end = false;
		}

	} while (end == false);
	exit;
}

void OpeningText()
{
	cout << "  _____          _  \n";
	Sleep(200);
	cout << " |  __ \\        | |   \n";
	Sleep(200);
	cout << " | |__) |__  ___| |_ \n";
	Sleep(200);
	cout << " |  ___/ _ \\/ __| __|\n";
	Sleep(200);
	cout << " | |  | (_) \\__ \\ |_\n";
	Sleep(200);
	cout << " |_|   \\___/|___/\\__|\n";
	Sleep(200);

	cout << "                                 _             _   _ \n";
	Sleep(200);
	cout << "     /\\                         | |           | | (_)\n";
	Sleep(200);
	cout << "    /  \\   _ __   ___   ___ __ _| |_   _ _ __ | |_ _  ___\n";
	Sleep(200);
	cout << "   / /\\ \\ | '_ \\ / _ \\ / __/ _` | | | | | '_ \\| __| |/ __|\n";
	Sleep(200);
	cout << "  / ____ \\| |_) | (_) | (_| (_| | | |_| | |_) | |_| | (__  \n";
	Sleep(200);
	cout << " /_/    \\_\\ .__/ \\___/ \\___\\__,_|_|\\__, | .__/ \\__|_|\\___|\n";
	Sleep(200);
	cout << "          | |                       __/ | | \n";
	Sleep(200);
	cout << "          |_|                      |___/|_|\n";
	Sleep(200);


	cout << "  _____ _       _           _ _\n";
	Sleep(200);
	cout << " |  __ (_)     | |         | | |\n";
	Sleep(200);
	cout << " | |__) | _ __ | |__   __ _| | |\n";
	Sleep(200);
	cout << " |  ___/ | '_ \\| '_ \\ / _` | | |\n";
	Sleep(200);
	cout << " | |   | | | | | |_) | (_| | | |\n";
	Sleep(200);
	cout << " |_|   |_|_| |_|_.__/ \\__,_|_|_|\n";
	Sleep(200);
}
