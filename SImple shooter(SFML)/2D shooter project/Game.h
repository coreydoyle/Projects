/// <summary>
/// author Corey Doyle 2023
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const int SCREEN_HEIGHT = 650;
const int SCREEN_WIDTH = 800;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processSpace(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setupFontAndText();
	void setupSprite();

	void setUpCharacterSprite();
	bool Game::checkPlayer(sf::Vector2f t_location);

	void enemy();
	void enemyMovement();
	bool checkEnemy(sf::RectangleShape& t_enemyLocation, sf::CircleShape& t_bullet, bool t_enemy);
	
	void enemy2();
	void enemyMovement2();
	bool checkEnemy2(sf::RectangleShape& t_enemyLocation2, sf::CircleShape& t_bullet, bool t_enemy2);

	void enemy3();
	void enemyMovement3();
	bool checkEnemy3(sf::RectangleShape& t_enemyLocation3, sf::CircleShape& t_bullet, bool t_enemy3);

	void enemy4();
	void enemyMovement4();
	bool checkEnemy4(sf::RectangleShape& t_enemyLocation4, sf::CircleShape& t_bullet, bool t_enemy4);


	void setUpFloorSprite();
	void setUpFloorSprite2();
	void setUpFloorSprite3();
	void setUpFloorSprite4();

	void setUpBulletSprite();
	void moveBullet();
	bool Game::checkWall(sf::Vector2f t_location);


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	
	sf::RectangleShape m_player; //Rectangle that represents player
	sf::Vector2f m_playerLocation; //location of player

	sf::RectangleShape m_floor; // Rectangle for floor
	sf::Vector2f m_floorLocation; //location for floor

	sf::RectangleShape m_floor2; //Rectangle for second floor
	sf::Vector2f m_floorLocation2; //location for second floor

	sf::RectangleShape m_floor3; //Rectangle for third floor
	sf::Vector2f m_floorLocation3; //location for third floor

	sf::RectangleShape m_floor4; //Rectangle for fourth floor
	sf::Vector2f m_floorLocation4; //location for fourth floor

	sf::CircleShape m_bullet; //circleshape for bullet
	sf::Vector2f m_bulletlocation; //location for bullet

	sf::Vector2f m_bulletVelocity{ 20.0f,0.0f }; //speed at which the bullet is fired at
	bool m_firing{ false }; // to show if the bullet should be fired or not

	sf::RectangleShape m_enemy; //Rectangle shape that represents the enemy
	sf::Vector2f m_enemyLocation; // location of enemy
	sf::Vector2f m_enemyVelocity{ 0.6f,0.0f }; //speed of the enemy
	bool enemyAlive{ true }; // checks to see if enemy is alive

	sf::RectangleShape m_enemy2;//Rectangle shape that represents the enemy
	sf::Vector2f m_enemyLocation2;// location of enemy
	sf::Vector2f m_enemyVelocity2{ 1.2f,0.0f };//speed of the enemy
	bool enemyAlive2{ true }; // checks to see if enemy is alive

	sf::RectangleShape m_enemy3;//Rectangle shape that represents the enemy
	sf::Vector2f m_enemyLocation3;// location of enemy
	sf::Vector2f m_enemyVelocity3{ 0.8f,0.0f }; //speed of the enemy
	bool enemyAlive3{ true }; // checks to see if enemy is alive

	sf::RectangleShape m_enemy4;//Rectangle shape that represents the enemy
	sf::Vector2f m_enemyLocation4;// location of enemy
	sf::Vector2f m_enemyVelocity4{ 0.2f,0.0f }; //speed of the enemy
	bool enemyAlive4{ true }; // checks to see if enemy is alive

	sf::Text m_killMessage; //string for kills
	int m_kill{ 0 }; //counter for kills

	sf::Text m_weaponMessage;//counter for changing weapons


	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

