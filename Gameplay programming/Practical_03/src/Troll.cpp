#include <./include/Troll.h>
using namespace std;

void Troll::setWeapon(int t_wepChoice)
{
    WeaponType wepType;
    if(t_wepChoice == 1)
    {
        cout << "Troll has picked Bat\n";
        wepType = WeaponType::BAT;
    }
    if(t_wepChoice == 2)
    {
        cout << "Troll has equipped Sword\n";
        wepType = WeaponType::SWORD;
    }
    if(t_wepChoice == 3)
    {
        cout << "Troll has wielded Shield\n";
        wepType = WeaponType::SHIELD;
    } 
    m_weapon->setType(wepType);
}
