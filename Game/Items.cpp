#include "Items.hpp"
#include <iostream>
using std::cout;

Items::Items()
{
	 m_money = 0;
	 m_scrap = 0;
	 m_ammo = 0;
	 m_snacks = 0;

	 m_gunparts = false;
	 m_spring = false;
	 m_gun = false;

	 m_claw = false;
	 m_motor = false;
	 m_rope = false;
	 m_grapple = false;

	 m_fuse = false;
	 m_TNT = false;
	 m_lighter = false;

	 m_key1 = false;
	 m_key2 = false;

	 m_sword = false;
	 m_goodGun = false;
	 m_luckyCharm = false;

}

void Items::ScrapChange(bool a, int b)
{
	if (a == false)
	{
		m_scrap -= b;
		if (m_scrap < 0)
			m_scrap = 0;
	}
	else
		m_scrap += b;
}

void Items::MoneyChange(bool a, int b)
{
	if (a == false)
	{
		m_money -= b;
		if (m_money < 0)
			m_money = 0;
	}
	else
		m_money += b;
}

void Items::AmmoChange(bool a, int b)
{
	if (a == false)
	{
		m_ammo -= b;
		if (m_ammo < 0)
			m_ammo = 0;
	}
	else
		m_ammo += b;
}

void Items::SnackChange(bool a, int b)
{
	if (a == false)
	{
		m_snacks -= b;
		if (m_snacks < 0)
			m_snacks = 0;
	}
	else
		m_snacks += b;
}

int Items::GetScrap(){return m_scrap;}

int Items::GetMoney(){return m_money;}

int Items::GetAmmo(){return m_ammo;}

int Items::GetSnack(){return m_snacks;}

void Items::KeyItemChange(int a)
{
	switch (a)
	{
	case 1:
		m_gunparts = true;
		break;
	case 2:
		m_spring = true;
		break;
	case 3:
		m_gun = true;
		break;
	case 4:
		m_claw = true;
		break;
	case 5:
		m_motor = true;
		break;
	case 6:
		m_rope= true;
		break;
	case 7:
		m_grapple = true;
		break;
	case 8:
		m_fuse = true;
		break;
	case 9:
		m_TNT = true;
		break;
	case 10:
		m_lighter = true;
		break;
	case 11:
		m_key1 = true;
		break;
	case 12:
		m_key2 = true;
		break;
	case 13:
		m_sword = true;
		break;
	case 14:
		m_goodGun = true;
		break;
	case 15:
		m_luckyCharm = true;
		break;
	}
}

bool Items::KeyItemCheck(int a)
{
	switch (a)
	{
	case 1:
		if (m_gunparts == true)
			return true;
		else return false;	break;
	case 2:
		if (m_spring == true)
			return true;
		else return false;	break;
	case 3:
		if (m_gun == true)
			return true;
		else return false;	break;
	case 4:
		if (m_claw == true)
			return true;
		else return false;	break;
	case 5:
		if (m_motor == true)
			return true;
		else return false;	break;
	case 6:
		if (m_rope == true)
			return true;
		else return false;	break;
	case 7:
		if (m_grapple == true)
			return true;
		else return false;	break;
	case 8:
		if (m_fuse == true)
			return true;
		else return false;	break;
	case 9:
		if (m_TNT == true)
			return true;
		else return false;	break;
	case 10:
		if (m_lighter == true)
			return true;
		else return false;	break;
	case 11:
		if (m_key1 == true)
			return true;
		else return false;	break;
	case 12:
		if (m_key2 == true)
			return true;
		else return false;	break;
	case 13:
		if (m_sword == true)
			return true;
		else return false;	break;
	case 14:
		if (m_goodGun == true)
			return true;
		else return false;	break;
	case 15:
		if (m_luckyCharm == true)
			return true;
		else return false;	break;
	}
}




void Items::DisplayInventory()
{
	system("CLS");
	cout << "\nMisc";
	cout << "\n--------";
	cout << "\nSnacks x " << m_snacks << "\n";
	cout << "Scraps x " << m_scrap <<  "\n";
	cout << "Ammo x " << m_ammo << "\n";
	cout << "Money x " << m_money << "\n";

	cout << "\n\nWeapons";
	cout << "\n--------";
	cout << "\nPipe\n";
	if (m_gun == true)
		cout << "Gun\n";
	if (m_sword == true)
		cout << "Sword\n";
	if (m_goodGun == true)
		cout << "Better Gun\n";

	cout << "\nKey Items";
	cout << "\n--------";

	if (m_key1 == true)
		cout << "\nKey 1";
	if (m_key2 == true)
		cout << "\nKey 2";

	if (m_luckyCharm == true)
		cout << "\nLucky Charm\n";

	if (m_gun == false)
	{
		if (m_gunparts == true)
			cout << "\nGun Parts";
		if (m_spring == true)
			cout << "\nSpring";
	}

	if (m_grapple == false)
	{
		if (m_claw == true)
			cout << "\nClaw";
		if (m_rope == true)
			cout << "\nRope";
		if (m_motor == true)
			cout << "\nMotor";
	}

	if (m_fuse == true)
		cout << "\nFuse";
	if (m_TNT == true)
		cout << "\nExplosive";
	if (m_lighter == true)
		cout << "\nLighter";



}
