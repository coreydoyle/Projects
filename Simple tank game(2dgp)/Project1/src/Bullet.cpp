#include <Bullet.h>

Bullet::Bullet(thor::ResourceHolder<sf::Texture, std::string>& t_holder)
	: m_holder(t_holder)
{
	initSprites();
}

void Bullet::update(double dt, bool &firing, sf::Vector2f tankpos, float turretrotation)
{
	if (firing == false)
	{
		bullet.setPosition(tankpos);
		rotation = turretrotation;
		bullet.setRotation(rotation);
	}
	else
	{
		
		float xPos = 0;
		float yPos = 0;

		xPos = bullet.getPosition().x + cos(rotation * MathUtility::DEG_TO_RAD) * speed * (dt / 1000);
		yPos = bullet.getPosition().y + sin(rotation * MathUtility::DEG_TO_RAD) * speed * (dt / 1000);

		bullet.setPosition(xPos, yPos);
		bullet.setRotation(rotation);
		if (bullet.getPosition().x < 0 || bullet.getPosition().x > ScreenSize::s_width
			|| bullet.getPosition().y < 0 || bullet.getPosition().y > ScreenSize::s_height)
		{
			firing = false;
		}
	}
	
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(bullet);
}

void Bullet::setPosition(sf::Vector2f t_position)
{
	bullet.setPosition(t_position);
}

sf::Sprite Bullet::getSprite()
{
	return bullet;
}

sf::Vector2f Bullet::getPosition()
{
	return bullet.getPosition();
}

void Bullet::setScale(sf::Vector2f t_scale)
{
	bullet.setScale(t_scale);
}

void Bullet::initSprites()
{
	m_holder.acquire("tankAtlas", thor::Resources::fromFile<sf::Texture>("resources/images/spritesheet.png"), thor::Resources::Reuse);
	sf::Texture& texture = m_holder["tankAtlas"];

	bullet.setTexture(texture);
	bullet.setTextureRect(sf::IntRect(247, 95, 128, 128));
	
	bullet.setOrigin(64, 64);

}
