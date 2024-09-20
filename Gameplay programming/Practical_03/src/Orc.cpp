#include <./include/Orc.h>
using namespace std;

void Orc::setWeapon(int t_wepChoice) {

    WeaponType wepType;
    if(t_wepChoice == 1)
    {
        cout << "Orc has picked Bat\n";
        wepType = WeaponType::BAT;
    }
    if(t_wepChoice == 2)
    {
        cout << "Orc has equipped Sword\n";
        wepType = WeaponType::SWORD;
    }
    if(t_wepChoice == 3)
    {
        cout << "Orc has wielded Shield\n";
        wepType = WeaponType::SHIELD;
    }
    m_weapon->setType(wepType);
}