/// <summary>
/// @author Corey Doyle
/// @date march 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "2D Shooter" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyPressed == newEvent.type) //user presed a key
		{
			processSpace(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::W == t_event.key.code) // user Presses key
	{
		if (m_firing) // if statment to see if the user is firing 
		{
			m_firing = false; // sets firing to false so it doesnt refire when moving to new floor
		}
		m_playerLocation = m_playerLocation - sf::Vector2f{ 0.0f, 150.0f }; //changes location of player by minus 150 on the y axis
		m_player.setPosition(m_playerLocation); //sets the position of the player
		m_bulletlocation = m_playerLocation; //sets the location of the bullet so that it may follow the player
		m_bullet.setPosition(m_bulletlocation); //sets the position of the bullet
	}
	if (sf::Keyboard::S == t_event.key.code) //user presses key
	{
		if (m_firing) // if statment to see if the user is firing 
		{
			m_firing = false; // sets firing to false so it doesnt refire when moving to new floor
		}
		m_playerLocation = m_playerLocation + sf::Vector2f{ 0.0f, 150.0f }; //changes location of player by plus 150 on the y axis
		m_player.setPosition(m_playerLocation); //sets the position of the player
		m_bulletlocation = m_playerLocation; //sets the location of the bullet so that it may follow the player
		m_bullet.setPosition(m_bulletlocation); //sets the position of the bullet
	}
	if (sf::Keyboard::E == t_event.key.code) //user presses key
	{
		m_bulletVelocity = sf::Vector2f{ 60.0f,0.0f }; // changes bullet velocity
		m_weaponMessage.setString("Weapon: Sniper"); //changes message displayed
	}
	if (sf::Keyboard::Q == t_event.key.code)//user presses key
	{
		m_bulletVelocity = sf::Vector2f{ 20.0f,0.0f };// changes bullet velocity
		m_weaponMessage.setString("Weapon: Pistol");//changes message displayed
	}

}

void Game::processSpace(sf::Event t_event)
{
	if (sf::Keyboard::Space == t_event.key.code) //user presses the space bar
	{
		if (!m_firing) // if statment for when not firing when space is pressed
		{
			m_firing = true; // sets firing bool to true so that the bullet will move
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_firing)
	{
		moveBullet();
		m_firing = checkWall(m_bulletlocation); //checks wall in relation to bullet location
		if (m_firing)
		{
			m_firing = checkEnemy(m_enemy, m_bullet, true);
		}
		if (m_firing)
		{
			m_firing = checkEnemy2(m_enemy2, m_bullet, true);
		}
		if (m_firing)
		{
			m_firing = checkEnemy3(m_enemy3, m_bullet, true);
		}
		if (m_firing)
		{
			m_firing = checkEnemy4(m_enemy4, m_bullet, true);
		}


	}
	
	checkPlayer(m_playerLocation); // checks player location at all times 
	enemyMovement(); // moves enemy
	enemyMovement2();// moves enemy
	enemyMovement3();// moves enemy
	enemyMovement4();// moves enemy
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.draw(m_player);

	if (enemyAlive == true)
	{
		m_window.draw(m_enemy);
	}
	if (enemyAlive2 == true)
	{
		m_window.draw(m_enemy2);
	}
	if (enemyAlive3 == true)
	{
		m_window.draw(m_enemy3);
	}
	if (enemyAlive4 == true)
	{
		m_window.draw(m_enemy4);
	}


	m_window.draw(m_floor);
	m_window.draw(m_floor2);
	m_window.draw(m_floor3);
	m_window.draw(m_floor4);


	m_window.draw(m_bullet);


	m_window.draw(m_killMessage);
	m_window.draw(m_weaponMessage);
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_killMessage.setCharacterSize(20U); //sets character size
	m_killMessage.setPosition(700.0f, 15.0f); //sets text position
	m_killMessage.setFillColor(sf::Color::Red); //sets text colour
	m_killMessage.setFont(m_ArialBlackfont); //sets font of text
	m_killMessage.setString("Kills:"); //sets string message

	m_weaponMessage.setCharacterSize(20U);//sets character size
	m_weaponMessage.setPosition(25.0f, 15.0f);//sets text position
	m_weaponMessage.setFillColor(sf::Color::Magenta);//sets text colour
	m_weaponMessage.setFont(m_ArialBlackfont);//sets font of text
	m_weaponMessage.setString("Weapon: Pistol"); //sets string message
	

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	setUpCharacterSprite();
	setUpFloorSprite();
	setUpFloorSprite2();
	setUpFloorSprite3();
	setUpFloorSprite4();
	setUpBulletSprite();
	enemy();
	enemy2();
	enemy3();
	enemy4();
}

void Game::setUpCharacterSprite()
{
	m_player.setFillColor(sf::Color::Red); //Creates the colour of the player rectangle
	m_player.setSize(sf::Vector2f{ 50.0f,75.0f }); //sets size of player rectangle
	m_player.setOrigin(50.0f, 20.0f); // sets origin of the player rectangle to the edge
	m_playerLocation = sf::Vector2f{ 70.0f,560.0f }; // defines the location of the player rectangle
	m_player.setPosition(m_playerLocation); //sets the position of the player rectangle
}

bool Game::checkPlayer(sf::Vector2f t_location)
{
	if (t_location.y > 560) // checks if the player is greater than this coord
	{
		m_playerLocation = sf::Vector2f{ 70.0f,560.0f }; //sets the player location back to first floor
		m_player.setPosition(m_playerLocation); //sets player position
		m_bulletlocation = m_playerLocation; //sets the bullet location so that it follows the player
		m_bullet.setPosition(m_bulletlocation); //sets the bullets position
		return false;
	}
	if (t_location.y < 0) //checks if the player is less than this coord
	{
		m_playerLocation = sf::Vector2f{ 70.0f, 110.0f }; //sets the players location to the fourth floor
		m_player.setPosition(m_playerLocation); //sets player position
		m_bulletlocation = m_playerLocation; //sets the bullet location so that it follows the player
		m_bullet.setPosition(m_bulletlocation); //sets the bullets position
		return false;
	}
	return true;
}

void Game::enemy()
{
	m_enemy.setFillColor(sf::Color::Green); //sets color of enemy
	m_enemy.setSize(sf::Vector2f{ 50.0f,75.0f }); //sets size of enemy
	m_enemy.setOrigin(50.0f, 20.0f); //sets origin of enemy
	m_enemyLocation = sf::Vector2f{ 630.0f,560.0f }; //sets location of enemy
	m_enemy.setPosition(m_enemyLocation); //sets position of enemy
}

void Game::enemyMovement()
{
	if (m_enemyLocation == sf::Vector2f{ 630.0f,560.0f }) //checks if enemy location is coords in statment
	{
		m_enemyVelocity = sf::Vector2f{ 0.6f,0.0f }; // changes enemy velocity
		enemyAlive = true; //sets alive bool to true
	}
	if (m_enemyLocation.x < 100.0f) //checks if enemys coords are less than coords in statment
	{
		m_enemyLocation = sf::Vector2f{ 630.0f,560.0f }; //sets enemy location
		m_enemy.setPosition(m_enemyLocation); //sets enemy position
	}
	m_enemyLocation -= m_enemyVelocity; //standard formula for movement 
	m_enemy.setPosition(m_enemyLocation); //sets position of enemy
}

bool Game::checkEnemy(sf::RectangleShape& t_enemyLocation, sf::CircleShape& t_bullet, bool t_enemy)
{
	bool result = true;
	sf::FloatRect circle = t_bullet.getGlobalBounds(); //gets global bounds for bullet
	sf::FloatRect box = t_enemyLocation.getGlobalBounds(); //gets global bounds for enemy
	if (circle.intersects(box)) //statment for if boxes collide
	{
		result = false;
		m_bulletlocation = m_playerLocation; //sets bullet location
		m_bullet.setPosition(m_bulletlocation); //sets bullet Position
		enemyAlive = false; //changes bool of enemy alive to false
		m_enemyVelocity = { 0.0f,0.0f }; //stops movement 
		m_enemyLocation = { 630.0f,560.0f }; //resets location
		m_kill++; //adds one to counter
		m_killMessage.setString("Kills: " + std::to_string(m_kill)); //displays message and counter
	}
	return result;
}

void Game::enemy2()
{
	m_enemy2.setFillColor(sf::Color::Cyan);//sets color of enemy
	m_enemy2.setSize(sf::Vector2f{ 50.0f,75.0f });//sets size of player rectangle
	m_enemy2.setOrigin(50.0f, 20.0f);//sets origin of enemy
	m_enemyLocation2 = sf::Vector2f{ 720.0f,410.0f };//sets location of enemy
	m_enemy2.setPosition(m_enemyLocation2);//sets position of enemy
}

void Game::enemyMovement2()
{
	if (m_enemyLocation2 == sf::Vector2f{ 720.0f,410.0f })//checks if enemy location is coords in statment
	{
		m_enemyVelocity2 = sf::Vector2f{ 1.2f,0.0f };// changes enemy velocity
		enemyAlive2 = true;//sets alive bool to true
	}
	if (m_enemyLocation2.x < 100.0f)//checks if enemys coords are less than coords in statment
	{
		m_enemyLocation2 = sf::Vector2f{ 720.0f,410.0f };//sets enemy location
		m_enemy2.setPosition(m_enemyLocation2);//sets enemy position
	}
	m_enemyLocation2 -= m_enemyVelocity2;//standard formula for movement 
	m_enemy2.setPosition(m_enemyLocation2);//sets position of enemy
}

bool Game::checkEnemy2(sf::RectangleShape& t_enemyLocation2, sf::CircleShape& t_bullet, bool t_enemy2)
{
	bool result = true;
	sf::FloatRect circle = t_bullet.getGlobalBounds();//gets global bounds for bullet
	sf::FloatRect box = t_enemyLocation2.getGlobalBounds();//gets global bounds for enemy
	if (circle.intersects(box))//statment for if boxes collide
	{
		result = false;
		m_bulletlocation = m_playerLocation;//sets bullet location
		m_bullet.setPosition(m_bulletlocation);//sets bullet Position
		enemyAlive2 = false;//changes bool of enemy alive to false
		m_enemyVelocity2 = { 0.0f,0.0f };//stops movement 
		m_enemyLocation2 = { 720.0f,410.0f };//resets location
		m_kill++;//adds one to counter
		m_killMessage.setString("Kills: " + std::to_string(m_kill));//displays message and counter
	}
	return result;
}



void Game::enemy3()
{
	m_enemy3.setFillColor(sf::Color::Yellow);//sets color of enemy
	m_enemy3.setSize(sf::Vector2f{ 50.0f,75.0f });//sets size of player rectangle
	m_enemy3.setOrigin(50.0f, 20.0f);//sets origin of enemy
	m_enemyLocation3 = sf::Vector2f{ 750.0f, 260.0f };//sets location of enemy
	m_enemy3.setPosition(m_enemyLocation3);//sets position of enemy
}

void Game::enemyMovement3()
{
	if (m_enemyLocation3 == sf::Vector2f{ 750.0f, 260.0f })//checks if enemy location is coords in statment
	{
		m_enemyVelocity3 = sf::Vector2f{ 0.8f,0.0f };// changes enemy velocity
		enemyAlive3 = true;//sets alive bool to true
	}
	if (m_enemyLocation3.x < 100.0f)//checks if enemys coords are less than coords in statment
	{
		m_enemyLocation3 = sf::Vector2f{ 750.0f, 260.0f };//sets enemy location
		m_enemy3.setPosition(m_enemyLocation3);//sets enemy position
	}
	m_enemyLocation3 -= m_enemyVelocity3;//standard formula for movement 
	m_enemy3.setPosition(m_enemyLocation3);//sets position of enemy
}

bool Game::checkEnemy3(sf::RectangleShape& t_enemyLocation3, sf::CircleShape& t_bullet, bool t_enemy3)
{
	bool result = true;
	sf::FloatRect circle = t_bullet.getGlobalBounds();//gets global bounds for bullet
	sf::FloatRect box = t_enemyLocation3.getGlobalBounds();//gets global bounds for enemy
	if (circle.intersects(box))//statment for if boxes collide
	{
		result = false;
		m_bulletlocation = m_playerLocation;//sets bullet location
		m_bullet.setPosition(m_bulletlocation);//sets bullet Position
		enemyAlive3 = false;//changes bool of enemy alive to false
		m_enemyVelocity3 = { 0.0f,0.0f };//stops movement 
		m_enemyLocation3 = { 750.0f, 260.0f };//resets location
		m_kill++;//adds one to counter
		m_killMessage.setString("Kills: " + std::to_string(m_kill));//displays message and counter
	}
	return result;
}



void Game::enemy4()
{
	m_enemy4.setFillColor(sf::Color::Magenta);//sets color of enemy
	m_enemy4.setSize(sf::Vector2f{ 50.0f,75.0f });//sets size of player rectangle
	m_enemy4.setOrigin(50.0f, 20.0f);//sets origin of enemy
	m_enemyLocation4 = sf::Vector2f{ 600.0f,110.0f };//sets location of enemy
	m_enemy4.setPosition(m_enemyLocation4);//sets position of enemy
}

void Game::enemyMovement4()
{
	if (m_enemyLocation4 == sf::Vector2f{ 600.0f,110.0f })//checks if enemy location is coords in statment
	{
		m_enemyVelocity4 = sf::Vector2f{ 0.2f,0.0f };// changes enemy velocity
		enemyAlive4 = true;//sets alive bool to true
	}
	if (m_enemyLocation4.x < 100.0f)//checks if enemys coords are less than coords in statment
	{
		m_enemyLocation4 = sf::Vector2f{ 600.0f,110.0f };//sets enemy location
		m_enemy4.setPosition(m_enemyLocation4);//sets enemy position
	}
	m_enemyLocation4 -= m_enemyVelocity4;//standard formula for movement 
	m_enemy4.setPosition(m_enemyLocation4);//sets position of enemy
}

bool Game::checkEnemy4(sf::RectangleShape& t_enemyLocation4, sf::CircleShape& t_bullet, bool t_enemy4)
{
	bool result = true;
	sf::FloatRect circle = t_bullet.getGlobalBounds();//gets global bounds for bullet
	sf::FloatRect box = t_enemyLocation4.getGlobalBounds();//gets global bounds for enemy
	if (circle.intersects(box))//statment for if boxes collide
	{
		result = false;
		m_bulletlocation = m_playerLocation;//sets bullet location
		m_bullet.setPosition(m_bulletlocation);//sets bullet Position
		enemyAlive4 = false;//changes bool of enemy alive to false
		m_enemyVelocity4 = { 0.0f,0.0f };//stops movement 
		m_enemyLocation4 = { 600.0f,110.0f };//resets location
		m_kill++;//adds one to counter
		m_killMessage.setString("Kills: " + std::to_string(m_kill));//displays message and counter
	}
	return result;
}



void Game::setUpFloorSprite()
{
	m_floor.setFillColor(sf::Color::White); //sets colour of floor
	m_floor.setSize(sf::Vector2f{ 800.0f, 32.0f }); //sets size of floor
	m_floorLocation = sf::Vector2f{ 0.0f, 615.0f }; //sets the location of the floor
	m_floor.setPosition(m_floorLocation); //sets the position of the floor
}

void Game::setUpFloorSprite2()
{
	m_floor2.setFillColor(sf::Color::White); //sets colour of the second floor
	m_floor2.setSize(sf::Vector2f{ 800.0f, 32.0f }); //sets the size of the second floor
	m_floorLocation2 = sf::Vector2f{ 0.0f, 465.0f }; //sets the location of the second floor
	m_floor2.setPosition(m_floorLocation2); //sets the position of the second floor
}

void Game::setUpFloorSprite3()
{
	m_floor3.setFillColor(sf::Color::White); //sets the color of the third floor
	m_floor3.setSize(sf::Vector2f{ 800.0f, 32.0f }); //sets the size of the third floor
	m_floorLocation3 = sf::Vector2f{ 0.0f, 315.0f }; //sets the location of the third floor
	m_floor3.setPosition(m_floorLocation3); //sets the position of the third floor
}

void Game::setUpFloorSprite4()
{
	m_floor4.setFillColor(sf::Color::White); //sets the color of the fourth floor
	m_floor4.setSize(sf::Vector2f{ 800.0f, 32.0f }); //sets the size of the fourth floor
	m_floorLocation4 = sf::Vector2f{ 0.0f, 155.0f }; //sets the location of the fourth floor
	m_floor4.setPosition(m_floorLocation4); //sets the position of the fourth floor
}

void Game::setUpBulletSprite()
{
	m_bullet.setFillColor(sf::Color::Blue); //sets the color of the circle for the bullet
	m_bullet.setRadius(5.0f); //sets the radius of the circle for the bullet
	m_bulletlocation = m_playerLocation; //sets the bullets location to the players location
	m_bullet.setPosition(m_bulletlocation); //sets the position of the bullet
}

void Game::moveBullet()
{
	m_bulletlocation += m_bulletVelocity; // standered formula for motion
	m_bullet.setPosition(m_bulletlocation); // sets the position of the bullet while being fired
}

bool Game::checkWall(sf::Vector2f t_location)
{
	if (t_location.x < 0.0f || t_location.x > 800.0f) // if statment to see check if the bullet passes these coords
	{
		m_bulletlocation = m_playerLocation; //sets the bullet location back to the players location
		m_bullet.setPosition(m_bulletlocation); // sets the position of the bullet back to where it was before being fired
		return false;
	}
	return true;
}