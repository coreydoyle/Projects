#include <./include/Character.h>
using namespace std;

Character::Character() {
    m_health = 100;
}
void Character::setHealth(int t_health) {
    m_health = t_health;
}

int Character::getHealth() {
    return m_health;
}

void Character::changeHealth(int t_health) {
    m_health += t_health;
}

Weapon* Character::getWeapon() {
    return m_weapon; 
}
