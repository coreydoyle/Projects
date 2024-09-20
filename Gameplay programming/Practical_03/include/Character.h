#ifndef CHARACTER_H
#define CHARACTER_H

#include <./include/Weapon.h>
#include <iostream>

// Abstract Character Class

class Character {
public:
	Character();
	void setHealth(int t_health); //sets health for character
	int getHealth(); //gets health for character
	void changeHealth(int t_health); // function to change health if needed 
	Weapon* getWeapon();
	virtual void setWeapon(int wepChoice) = 0;

private:
	int m_health;
protected:
	Weapon* m_weapon = new Weapon();
};
#endif