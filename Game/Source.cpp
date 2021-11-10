#include "Location.hpp"
#include <iostream>
#include <stdbool.h>
#include "Functions.hpp"
#include "Enemy.hpp"
#include"Player.hpp"
#include "Weapons.hpp"
#include <stdlib.h>
#include <windows.h>
#include <chrono>
#include <random>
#define random(min, max) rand() % (max + 1 - min) + min
using std::cout;
using std::cin;
using std::string;


int main()
{
	int m_luck = 7;

	srand((unsigned)time(0));
	if (m_luck * (random(m_luck, 6)) >= 20);

	Location Base(161, 1, 6, false);
	string name;
	Weapons Mop(10, 1, "Mop");
	Items Inventory;
	Enemy StartMonster(50, 1, "Sob", false, 1, 5);
	cout << "\n  ____________";
	cout << "\n | Welcome to |";
	cout << "\n |____________|\n\n";
	OpeningText();

	cout << "\n\nWhat is your name?\n";
	cin >> name;
	Player Gamer(100, 3, name, false, 1, false);
	cout << "\nWelcome " << name << " I hope you enjoy my game :)";
	Sleep(2000);
	system("CLS");
	cout << "\nYou wake up to a loud banging on your apartment's door\n"
		"You get up and walk over to the door only to realise that your bed is awfully close to the door\n"
		"And your bed is a concrete floor\n"
		"And your bedroom is incredibly small\n\n";
	Sleep(4000);
	system("CLS");
	cout <<	"You wake up in a closet to a loud banging on the door\n"
		"You go towards the door with the intent of opening it but the sound of groaning makes you hesitate\n"
		"You stand frozen infront of the door until a hand breaks though the flimsy wood\n"
		"In a panic, you grab the nearest weapon... a mop\n\n"
		"The door finally gives way to reveal a zombie your first foe\n\n"
		"You ready your mop and prepare to strike!\n";
	
	StartFight(Gamer, StartMonster, Mop);
	if (Gamer.GetDeath() == true)
	{
		cout << "\nYou died! Have fun starting over from the beginning!\n";
		exit;
	}
	Inventory.MoneyChange(true, 10);
	Inventory.ScrapChange(true, 5);
	Gamer.LevelUp();
	cout << "\nYou have won your first battle!\n";

	cout << "\nThe zombie drops to the ground\n"
		"You heave a sigh of relief and look forward into whatever building owns the closet you woke up in\n\n"
		"It's an arcade, a sizeable one at that with lights and sounds blasting out of machines in an almost overwhelming manner\n"
		"You immediately decide to find a better weapon, you settle with a solid water pipe you ripped off the wall"
		"Looking back into the closet, you find a map of the arcade on a corner shelf\n"
		"You find your bag next to the map in the back corner, it's empty for now but maybe you could scavenge some materials to fill it with\n"
		"There's only one way forward - forward\n";

	cout << "\nW = North\nA = West\nS = South\nD = East\n\nM = Map\nI = Inventory\nU = Show player stats\nL = Look\n";

	do
	{
		UserInput(Base, Inventory, Gamer);
	} while(Gamer.GetComplete() == false);

	if (Gamer.GetDeath() == true)
	{
		cout << "\nYou died! Have fun starting over from the beginning!\n";
		exit;
	}
	else
	{
		cout << "                       .|\n"
			"                       | |\n"
			"                       |'|            ._____\n"
			"               ___    |  |            |.   |' .---'|\n"
			"       _    .-'   '-. |  |     .--'|  ||   | _|    |\n"
			"    .-'|  _.|  |    ||   '-__  |   |  |    ||      |\n"
			"    |' | |.    |    ||       | |   |  |    ||      |\n"
			" ___|  '-'     '    ''       '-'   '-.'    '`	   |____\n"
			"_________________________________________________________\n"
			"	 _____ _                           _ \n"
			"	|_   _| |                         | |\n"
			"	  | | | |__   ___    ___ _ __   __| |\n"
			"	  | | | '_ \\ / _ \\  / _ \\ '_ \\ / _` |\n"
			"	  | | | | | |  __/ |  __/ | | | (_| |\n"
			"	  \\_/ |_| |_|\\___|  \\___|_| |_|\\__,_|\n";
	}
}


