#include "Tank.h"
#include "LevelLoader.h"
#include "CollisionDetector.h"

Tank::Tank(thor::ResourceHolder<sf::Texture, std::string>& t_holder,
	std::vector<sf::Sprite>& t_wallSprites)
	: m_holder(t_holder),
	m_wallSprites(t_wallSprites)
{
	initSprites();
}

void Tank::update(double dt)
{

	if (checkWallCollision())
	{
		m_state = TankState::COLLIDING;
	}
	else
	{
		m_state = TankState::NORMAL;
	}

	switch (m_state)
	{
	case TankState::NORMAL:
		handleKeyinput();
		break;
	case TankState::COLLIDING:
		deflect(dt);
		break;
	default:
		break;
	}

	float xPos = 0;
	float yPos = 0;


	m_speed = std::clamp(m_speed, MAX_REVERSE_SPEED, MAX_FORWARD_SPEED);

	xPos = m_tankBase.getPosition().x + cos(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000);
	yPos = m_tankBase.getPosition().y + sin(m_rotation * MathUtility::DEG_TO_RAD) * m_speed * (dt / 1000);

	m_tankBase.setPosition(xPos, yPos);
	m_turret.setPosition(xPos, yPos);

	m_tankBase.setRotation(m_rotation);
	m_turret.setRotation(m_turretrotation);

	handleKeyinput();

	if (m_fireRequested == true)
	{
		m_shootTimer -= dt;

		if (m_shootTimer <= 0)
		{
			m_shootTimer = s_TIME_BETWEEN_SHOTS;
			m_fireRequested = false;
		}
	}
	m_pool.update(dt,m_wallSprites);

	if (rotateFlag == true)
	{
		centreTurret();
	}

	m_speed *= 0.99;
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	m_pool.render(window);
}

void Tank::setPosition(sf::Vector2f t_position)
{
	m_tankBase.setPosition(t_position);
	m_turret.setPosition(t_position);
}

sf::Vector2f Tank::getPosition()
{
	return m_tankBase.getPosition();
}


void Tank::setScale(sf::Vector2f t_scale)
{
	m_tankBase.setScale(t_scale);
	m_turret.setScale(t_scale);
}

void Tank::requestFire()
{
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		sf::Vector2f tipOfTurret(m_turret.getPosition().x, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(MathUtility::DEG_TO_RAD * m_turret.getRotation()) *
			((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height));
		tipOfTurret.y += std::sin(MathUtility::DEG_TO_RAD * m_turret.getRotation()) *
			((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height));
		m_pool.create(m_holder["tankAtlas"], tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
}

void Tank::increaseSpeed()
{
	m_speed += 5;
}

void Tank::decreaseSpeed()
{
	m_speed -= 5;
}

void Tank::increaseRotation()
{
	m_rotation += 1; 
	m_turretrotation += 1;
	if (m_rotation == 360.0 && m_turretrotation == 360) { 
		m_rotation = 0; 
		m_turretrotation = 0;
	}
}


void Tank::decreaseRotation()
{
	m_rotation -= 1; 
	m_turretrotation -= 1;
	if (m_rotation < 0.0 && m_turretrotation < 0.0) {
		m_rotation = 359.0; 
		m_turretrotation = 359.0;
	}
}

void Tank::increaseTurretRotation()
{
	m_turretrotation += 1;
	if (m_turretrotation == 360.0) {
		m_turretrotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_turretrotation -= 1;
	if (m_turretrotation < 0.0) {
		m_turretrotation = 359.0;
	}
}

void Tank::centreTurret()
{
	if (m_turretrotation < m_rotation)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}
	
	if (abs(m_turretrotation - m_rotation) > 180)
	{
		direction = -direction;
	}

	if (m_turretrotation == 360.0f)
	{
		m_turretrotation = 0;
	}
	else if (m_turretrotation < 0.0f)
	{
		m_turretrotation = 359.0f;
	}

	m_turretrotation += direction;

	if (m_turretrotation == m_rotation)
	{
		rotateFlag = false;
	}
		
}

void Tank::handleKeyinput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		increaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		decreaseTurretRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		rotateFlag = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		requestFire();
	}
}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_turret, sprite))
		{
			if (CollisionDetector::pixelPerfectTest(m_turret, sprite))
			{
				m_contactNormal = m_turret.getPosition() - sprite.getPosition();
				return true;
			}
			
		}
		else if (CollisionDetector::collision(m_tankBase, sprite))
		{
			m_contactNormal = m_tankBase.getPosition() - sprite.getPosition();
			return true;
		}
	}
	return false;
}

void Tank::deflect(double dt)
{
	float impulseMagnitude = std::abs(m_speed);
	m_contactNormal = thor::unitVector(m_contactNormal);
	sf::Vector2f deflectVector =
	{

	impulseMagnitude * m_contactNormal.x * (static_cast<float>(dt) / 1000),

	impulseMagnitude * m_contactNormal.y * (static_cast<float>(dt) / 1000)

	};
	m_tankBase.move(deflectVector.x, deflectVector.y);
	m_turret.move(deflectVector.x, deflectVector.y);
}

void Tank::initSprites()
{

	m_holder.acquire("tankAtlas", thor::Resources::fromFile<sf::Texture>("resources/images/spritesheet.png"));
	sf::Texture& texture = m_holder["tankAtlas"];
	
	m_tankBase.setTexture(texture);
	m_tankBase.setTextureRect(sf::IntRect(0, 95, 246, 114));
	
	m_tankBase.setOrigin(88, 59);
	m_tankBase.setRotation(m_rotation);
	
	

	m_turret.setTexture(texture);
	m_turret.setTextureRect(sf::IntRect(247, 0, 191, 94));
	
	m_turret.setOrigin(45, 47);
	m_turret.setRotation(m_rotation);
	
	
}