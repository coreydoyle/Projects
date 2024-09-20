#include <./include/Weapon.h>
#include<iostream>

Weapon::Weapon() {

}

int Weapon::GetDamage() {
    return m_damage; // returns the damage that the weapon deals
}

int Weapon::GetCooldown() {
    return m_cooldown;
}

void Weapon::setType(WeaponType t_type)
{
    type = t_type;

    if(type == WeaponType::BAT)
    {
        type = WeaponType::BAT; // assigns the Bat weapon type to the variable 
        m_damage = 15; // sets damage for the weapon type bat 
    }
    if(type == WeaponType::SWORD)
    {
        type = WeaponType::SWORD; // assigns the Sword weapon type to the variable
        m_damage = 20; // sets damage for the weapon type sword
    }
    if(type == WeaponType::SHIELD)
    {
        type = WeaponType::SHIELD; // assigns the Shield weapon type to the variable
        m_damage = 10; // sets damage for the weapon type shield 
    }
    
}
