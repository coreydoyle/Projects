#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "LevelLoader.h"
#include "MathUtility.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
/// <summary> 
/// @brief Constructor that stores drawable state (texture, sprite) for the 
///  tank. 
///  Stores references to the resource holder and container of wall sprites. 
///  Creates sprites for the tank base and turret from the texture in the	
///  resource holder. 	
///  </summary> 
///  <param name="t_holder">A reference to the resource holder</param> 
/// < param name="t_wallSprites">A reference to the container of wall
///  sprites </param>

enum class TankState {NORMAL, COLLIDING};


class Tank
{
public:	
	Tank(thor::ResourceHolder <sf::Texture, std::string>& t_holder,
		std::vector<sf::Sprite>& t_wallSprites);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();
	void setScale(sf::Vector2f t_scale);
	LevelData m_level;

	/// <summary> 
	/// @brief Increases the speed by 1. 
	///
	/// </summary> 
	void increaseSpeed();  
	
	/// <summary> 
	/// @brief Decreases the speed by 1. 
	/// 
	/// </summary> 
	void decreaseSpeed();

	/// <summary> 
	/// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359. 
	/// 
	/// </summary> 
	void increaseRotation();

	/// <summary> 
	/// @brief Decreases the rotation by 1 degree, wraps to 359 degrees after 0. 
	/// 
	/// </summary> 
	void decreaseRotation();

	void increaseTurretRotation();
	
	void decreaseTurretRotation();

	void centreTurret();

	void handleKeyinput();

	bool checkWallCollision();

	void deflect(double dt);

	TankState m_state{ TankState::NORMAL };

private:
	void initSprites();
	thor::ResourceHolder<sf::Texture, std::string> &m_holder;
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	std::vector<sf::Sprite>& m_wallSprites;
	// The tank speed. 
	double m_speed{ 0.0 };
	// The current rotation as applied to tank base. 
	double m_rotation{ 0.0 };
	double m_turretrotation{ 0.0 };
	bool rotateFlag = false;
	int direction = 0;
	const double MAX_REVERSE_SPEED = -100;
	const double MAX_FORWARD_SPEED = 100;
	sf::Vector2f m_contactNormal;
};