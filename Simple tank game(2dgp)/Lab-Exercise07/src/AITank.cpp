#include "AITank.h"

////////////////////////////////////////////////////////////
AITank::AITank(sf::Texture const & texture, std::vector<sf::Sprite> & wallSprites)
	: m_aiBehaviour(AiBehaviour::SEEK_PLAYER)
	, m_texture(texture)
	, m_wallSprites(wallSprites)
	, m_steering(0, 0)
{
	// Initialises the tank base and turret sprites.
	initSprites();
}



////////////////////////////////////////////////////////////
void AITank::update(Tank &playerTank, double dt)
{

	sf::Vector2f vectorToPlayer = seek(playerTank.getPosition());	
	switch (m_aiBehaviour)
	{
		case AiBehaviour::SEEK_PLAYER:
			m_steering += thor::unitVector(vectorToPlayer);
			m_steering += collisionAvoidance();
			m_steering = MathUtility::truncate(m_steering, MAX_FORCE);
			m_velocity = MathUtility::truncate(m_velocity + m_steering, MAX_SPEED);				
			break;
	
		case AiBehaviour::STOP:
			m_velocity = sf::Vector2f(0, 0);
			break;
		default:
			break;
	}
	
	// Now we need to convert our velocity vector into a rotation angle between 0 and 359 degrees.
	// The m_velocity vector works like this: vector(1,0) is 0 degrees, while vector(0, 1) is 90 degrees.
	// So for example, 223 degrees would be a clockwise offset from 0 degrees (i.e. along x axis).
	// Note: we add 180 degrees below to convert the final angle into a range 0 to 359 instead of -PI to +PI
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / std::numbers::pi * 180 + 180;

	auto currentRotation = m_rotation;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}

	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation = static_cast<int>((m_rotation) - 1) % 360;
	}


	if (thor::length(vectorToPlayer) < MAX_SEE_AHEAD)
	{
		m_aiBehaviour = AiBehaviour::STOP;
	}
	else
	{
		m_aiBehaviour = AiBehaviour::SEEK_PLAYER;
	}

	updateMovement(dt);

}

////////////////////////////////////////////////////////////
void AITank::render(sf::RenderWindow & window)
{
	// TODO: Don't draw if off-screen...
	window.draw(m_tankBase);
	window.draw(m_turret);	
}

////////////////////////////////////////////////////////////
void AITank::init(sf::Vector2f t_position, sf::Vector2f t_scale)
{
	m_tankBase.setPosition(t_position);
	m_tankBase.setScale(t_scale.x, t_scale.y);
	m_turret.setPosition(t_position);
	m_turret.setScale(t_scale.x, t_scale.y);

	for (sf::Sprite const wallSprite : m_wallSprites)
	{
		sf::CircleShape circle(wallSprite.getTextureRect().width * 1.5f); 
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(wallSprite.getPosition());
		m_obstacles.push_back(circle);
	}
}

////////////////////////////////////////////////////////////
sf::Vector2f AITank::seek(sf::Vector2f t_playerPosition) const
{
	sf::Vector2f search;
	search.x = t_playerPosition.x - m_tankBase.getPosition().x;
	search.y = t_playerPosition.y - m_tankBase.getPosition().y;
	// This return statement is simply a placeholder and must be changed...
	return search;	
}

////////////////////////////////////////////////////////////
sf::Vector2f AITank::collisionAvoidance()
{
	auto headingRadians = thor::toRadian(m_rotation);
	sf::Vector2f headingVector(std::cos(headingRadians) * MAX_SEE_AHEAD, std::sin(headingRadians) * MAX_SEE_AHEAD);
	m_ahead = m_tankBase.getPosition() + headingVector;
	m_halfAhead = m_tankBase.getPosition() + (headingVector * 0.5f);
	// Returns a copy of the argument rotated by the specified amount in degrees.
	sf::Vector2f left = thor::rotatedVector(headingVector * 0.5f, -45.0f);
	m_aheadLeft = m_tankBase.getPosition() + left;
	sf::Vector2f right = thor::rotatedVector(headingVector * 0.5f, 45.0f);
	m_aheadRight = m_tankBase.getPosition() + right;

	m_aheadVector.setPosition(m_tankBase.getPosition());
	m_aheadVector.setSize({ thor::length(headingVector), 1.0f });
	m_aheadVector.setFillColor(sf::Color::Red);
	m_aheadVector.setRotation(m_rotation);

	m_aheadLeftVector.setPosition(m_tankBase.getPosition());
	m_aheadLeftVector.setSize({ thor::length(left), 1.0f });
	m_aheadLeftVector.setFillColor(sf::Color::Red);
	m_aheadLeftVector.setRotation(m_rotation - 45.0f);

	m_aheadRightVector.setPosition(m_tankBase.getPosition());
	m_aheadRightVector.setSize({ thor::length(right), 1.0f });
	m_aheadRightVector.setFillColor(sf::Color::Red);
	m_aheadRightVector.setRotation(m_rotation + 45.0f);

	sf::Vector2f collisionVector = findMostThreateningObstacle();

	sf::Vector2f avoidance(0, 0);

	if (m_mostThreatening != nullptr)
	{
		avoidance.x = collisionVector.x - m_mostThreatening->getPosition().x;
		avoidance.y = collisionVector.y - m_mostThreatening->getPosition().y;
		avoidance = thor::unitVector(avoidance);
		avoidance *= MAX_AVOID_FORCE;
	}
	else
	{
		avoidance *= 0.0f;
	}

	return avoidance;
}


////////////////////////////////////////////////////////////
sf::Vector2f AITank::findMostThreateningObstacle()
{	
	m_mostThreatening = nullptr;
	double shortestDistance = 0.0;
	sf::Vector2f collisionVector;
	// Complete....
	for (sf::CircleShape circle : m_obstacles)
	{
		bool collidesAhead = MathUtility::lineIntersectsCircle(m_ahead, m_halfAhead, circle);
		if (collidesAhead)
		{
			collisionVector = m_ahead;

			if (shortestDistance == 0.0)
			{
				shortestDistance = MathUtility::distance(circle.getPosition(), m_tankBase.getPosition());
				m_mostThreatening = &circle;
			}
			else if (MathUtility::distance(circle.getPosition(), m_tankBase.getPosition()) < shortestDistance)
			{
				m_mostThreatening = &circle;
			}
		}

		bool collidesRight = MathUtility::lineIntersectsCircle(m_aheadRight, m_halfAhead, circle);
		if (collidesRight)
		{
			collisionVector = m_aheadRight;

			if (shortestDistance == 0.0)
			{
				shortestDistance = MathUtility::distance(circle.getPosition(), m_tankBase.getPosition());
				m_mostThreatening = &circle;
			}
			else if (MathUtility::distance(circle.getPosition(), m_tankBase.getPosition()) < shortestDistance)
			{
				m_mostThreatening = &circle;
			}
		}

		bool collidesLeft = MathUtility::lineIntersectsCircle(m_aheadLeft, m_halfAhead, circle);
		if (collidesLeft)
		{
			collisionVector = m_aheadLeft;

			if (shortestDistance == 0.0)
			{
				shortestDistance = MathUtility::distance(circle.getPosition(), m_tankBase.getPosition());
				m_mostThreatening = &circle;
			}
			else if (MathUtility::distance(circle.getPosition(), m_tankBase.getPosition()) < shortestDistance)
			{
				m_mostThreatening = &circle;
			}
		}
	}

	return collisionVector;
	

}

////////////////////////////////////////////////////////////
void AITank::initSprites()
{	
	// BrownTank,0,138,244,114
	// Gun_01_Brown,0,253,212,94
	sf::IntRect brownTankRect(0, 233, 244, 114);
	m_tankBase.setTexture(m_texture);
	m_tankBase.setTextureRect(brownTankRect);

	m_tankBase.setOrigin(88, brownTankRect.height / 2.0);
	m_tankBase.setPosition(sf::Vector2f(200, 200));

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(0, 0, 212, 94);
	m_turret.setTextureRect(turretRect);

	m_turret.setOrigin(45, turretRect.height / 2.0);
}


////////////////////////////////////////////////////////////
void AITank::updateMovement(double dt)
{
	double speed = thor::length(m_velocity);
	sf::Vector2f newPos(m_tankBase.getPosition().x + std::cos(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000),
		m_tankBase.getPosition().y + std::sin(MathUtility::DEG_TO_RAD  * m_rotation) * speed * (dt / 1000));
	m_tankBase.setPosition(newPos.x, newPos.y);
	m_tankBase.setRotation(m_rotation);
	m_turret.setPosition(m_tankBase.getPosition());
	m_turret.setRotation(m_rotation);
}