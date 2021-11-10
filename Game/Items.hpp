#pragma once
class Items
{
private:
	int m_money;
	int m_scrap;
	int m_ammo;
	int m_snacks;

	bool m_gunparts;
	bool m_spring;
	bool m_gun;
	bool m_claw;
	bool m_motor;
	bool m_rope;
	bool m_grapple;
	bool m_fuse;
	bool m_TNT;
	bool m_lighter;
	bool m_key1;
	bool m_key2;
	bool m_sword;
	bool m_goodGun;
	bool m_luckyCharm;

public:
	Items();
	void ScrapChange(bool a, int b);
	void MoneyChange(bool a, int b);
	void AmmoChange(bool a, int b);
	void SnackChange(bool a, int b);
	int GetScrap();
	int GetMoney();
	int GetAmmo();
	int GetSnack();
	void KeyItemChange(int a);
	bool KeyItemCheck(int a);
	void DisplayInventory();
};

