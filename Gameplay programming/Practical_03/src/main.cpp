#include <iostream>
#include <./include/Orc.h>
#include <./include/Troll.h>

using namespace std;

int main() {
	Orc orc; // creates reference for orc
	Troll troll; // creates reference for troll
	int character = 0; // choice for player to choose character
	bool choice = false; // bool to allow while loop to loop without errors 
	Character* player; // Character pointer to the player
	Character* npc; // Character pointer to the enemy/npc
	int pWeaponChoice;
	int eWeaponChoice;
	srand(time(NULL));

	while(choice == false)
	{
		cout<<"Choose a Character\n1: Orc\n2: Troll\n";
		cin >> character;

		if(character == 1)
		{
			player = &orc; 
			npc = &troll;
			cout<<"You have selected Orc\n";
			choice = true;
		}
		else if(character == 2)
		{
			player = &troll;
			npc = &orc;
			cout<<"You have selected Troll\n";
			choice = true;
		}
		else
		{
			cout<< "Invalid option"<<'\n';
			choice = false;
		}
	}

	while(player->getHealth() > 0 && npc->getHealth() > 0)
	{
		//player choice
		cout << "Please choose a weapon\n1: Bat\n2: Sword\n3: Shield\n";
		cin >> pWeaponChoice;
		player->setWeapon(pWeaponChoice);

		//npc choice
		cout << "Opponent is choosing a weapon\n";
		eWeaponChoice = rand() % 3 + 1;
		npc->setWeapon(eWeaponChoice);

		//damage taken
		player->changeHealth(-npc->getWeapon()->GetDamage());
		npc->changeHealth(-player->getWeapon()->GetDamage());
		if(npc->getHealth() < 0)
		{
			npc->setHealth(0);
		}
		if(player->getHealth() < 0)
		{
			player->setHealth(0);
		}
		cout << "Player health: " << player->getHealth() << '\n';
		cout << "Opponent health: " << npc->getHealth() << '\n';
	}

	if(npc->getHealth() <= 0 && player->getHealth() <= 0)
	{
		cout << "Nobody wins" << '\n';
	}
	else if(npc->getHealth() <= 0)
	{
		cout << "Player wins" << '\n';
	}

	else if(player->getHealth() <= 0)
	{
		cout << "Opponent wins" << '\n';
	}
		

	
	cin.get();

}