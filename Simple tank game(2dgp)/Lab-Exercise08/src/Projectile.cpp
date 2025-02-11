#include "Projectile.h"

////////////////////////////////////////////////////////////
void Projectile::init(sf::Texture const & t_texture, double t_x, double t_y, double t_rotation)
{	
	m_projectile.setTexture(t_texture);
	m_projectile.setTextureRect(m_projectileRect);
	m_projectile.setOrigin(m_projectileRect.width / 2.0, m_projectileRect.height / 2.0);
	m_projectile.setPosition(t_x, t_y);
	
	m_projectile.setRotation(t_rotation); 
	m_speed = s_MAX_SPEED;
}

////////////////////////////////////////////////////////////
bool Projectile::update(double t_dt, std::vector<sf::Sprite> & t_wallSprites, std::function<void(int)>& t_funcApplyDamage, sf::Sprite t_tankBase)
{
	if (!inUse())
	{
		// If this projectile is not in use, there is no update routine to perform.
		return false;
	}
	
	sf::Vector2f position = m_projectile.getPosition();
	sf::Vector2f newPos(position.x + std::cos(MathUtility::DEG_TO_RAD  * m_projectile.getRotation()) * m_speed * (t_dt / 1000),
		position.y + std::sin(MathUtility::DEG_TO_RAD  * m_projectile.getRotation()) * m_speed * (t_dt / 1000));

	m_projectile.setPosition(newPos.x, newPos.y);

	if (!isOnScreen(newPos)) 
	{
		m_speed = 0;	
	}
	else 
	{
		// Still on-screen, have we collided with a wall?
		for (sf::Sprite const & sprite : t_wallSprites)
		{
			// Checks if the projectile has collided with the current wall sprite.
			if (CollisionDetector::collision(m_projectile, sprite)) 
			{
				m_speed = 0;
			}
		}		
	}
	if (CollisionDetector::collision(m_projectile, t_tankBase))
	{
		t_funcApplyDamage(1);
		m_speed = 0;
	}
	return m_speed == s_MAX_SPEED;
}

////////////////////////////////////////////////////////////
bool Projectile::inUse() const 
{ 
	// Projectile is not in use if not moving.
	return m_speed == s_MAX_SPEED; 
}

////////////////////////////////////////////////////////////
bool Projectile::isOnScreen(sf::Vector2f t_position) const
{	
	return t_position.x - m_projectileRect.width / 2 > 0.f
		&& t_position.x + m_projectileRect.width / 2 < ScreenSize::s_width
	    && t_position.y - m_projectileRect.height / 2 > 0.f
		&& t_position.y + m_projectileRect.height / 2 < ScreenSize::s_height;
}