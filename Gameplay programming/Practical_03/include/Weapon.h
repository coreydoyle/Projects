#ifndef Weapon_H
#define Weapon_H

enum WeaponType {
    BAT,
    SWORD,
    SHIELD
};


class Weapon {
public:

    Weapon();
    int GetDamage(); //gets damage for the weapons
    int GetCooldown(); //Cooldown for the weapons
    void setType(WeaponType t_type); //sets the weapon type

private:
    int m_damage;
    int m_cooldown;
    WeaponType type;
};
#endif