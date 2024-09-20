#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "MathUtility.h"
#include <ScreenSize.h>

class Bullet
{
public:
	Bullet(thor::ResourceHolder <sf::Texture, std::string>& t_holder);
	void update(double dt, bool &firing, sf::Vector2f tankpos, float turretrotation);
	void render(sf::RenderWindow& window);
	void setPosition(sf::Vector2f t_position);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void setScale(sf::Vector2f t_scale);

private:
	void initSprites();
	thor::ResourceHolder<sf::Texture, std::string>& m_holder;
	double speed{1000.0f};
	double rotation{ 0.0f };
	sf::Sprite bullet;
};
