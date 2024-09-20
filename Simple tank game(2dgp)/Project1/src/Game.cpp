#include "Game.h"
#include <iostream>

// Our target FPS
static double const FPS{ 60.0f };

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_tank(m_holder, m_wallSprites, m_targetSprite)
{
	init();

}

////////////////////////////////////////////////////////////
void Game::init()
{

	
	// Really only necessary is our target FPS is greater than 60.
	m_window.setVerticalSyncEnabled(true);

	if (!m_arialFont.loadFromFile("BebasNeue.otf"))
	{
		std::cout << "Error loading font file";
	}

	sf::Texture& texture = m_holder["tankAtlas"];

	m_holder.acquire("background", thor::Resources::fromFile<sf::Texture>("resources/images/Background.jpg"));
	sf::Texture& bgtexture = m_holder["background"];

	m_holder.acquire("target", thor::Resources::fromFile<sf::Texture>("resources/images/target.png"));
	sf::Texture& targetTexture = m_holder["target"];


	int currentLevel = 1;

	try
	{ 
		LevelLoader::load(currentLevel, m_level); 
	}
	catch (std::exception& e) 
	{ 
		std::cout << "Level Loading failure." << std::endl; std::cout << e.what() << std::endl; throw e; 
	}


	for (auto const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sf::IntRect wallRect(0, 210, 32, 22); // Create the Walls 
		sprite.setTextureRect(wallRect); sprite.setOrigin(
			wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);

	}

	for (auto const& target : m_level.m_target)
	{
		sf::Sprite sprite;
		sprite.setTexture(targetTexture);
		sprite.setScale(target.m_scale, target.m_scale);
		sprite.setPosition(target.m_position);
		sprite.setRotation(target.m_rotation);
		m_targetSprite.push_back(sprite);
	}


	m_tank.setPosition(m_level.m_tank.m_position);
	m_tank.setScale(sf::Vector2f(m_level.m_tank.m_scale, m_level.m_tank.m_scale));

	m_bgSprite.setTexture(bgtexture);

	m_timer.setFont(m_arialFont);
	m_timer.setPosition(0, 0);
	m_timer.setCharacterSize(30U);
	m_timer.setFillColor(sf::Color::White);
	m_timer.setOutlineColor(sf::Color::Black);
	m_timer.setOutlineThickness(2.0f);
	m_timer.setString("Time: " + std::to_string(timercount));

	score.setFont(m_arialFont);
	score.setPosition(0, 50);
	score.setCharacterSize(30U);
	score.setFillColor(sf::Color::White);
	score.setOutlineColor(sf::Color::Black);
	score.setOutlineThickness(2.0f);
	score.setString("Score: " + std::to_string(scorecount));

	accuracy.setFont(m_arialFont);
	accuracy.setPosition(0, 100);
	accuracy.setCharacterSize(30U);
	accuracy.setFillColor(sf::Color::White);
	accuracy.setOutlineColor(sf::Color::Black);
	accuracy.setOutlineThickness(2.0f);
	accuracy.setString("Accuracy: " + std::to_string(percentagehit) + "%");

	endtext.setFont(m_arialFont);
	endtext.setPosition(500, 250);
	endtext.setCharacterSize(90U);
	endtext.setFillColor(sf::Color::White);
	endtext.setOutlineColor(sf::Color::Black);
	endtext.setOutlineThickness(2.0f);
	endtext.setString("GameOver \n Score was " + std::to_string(scorecount) + "\n and Accuracy was " + std::to_string(percentagehit) + "%");

	//m_targetSprites.setTexture(targetTexture);
	/*m_targetSprites.setScale(0.25, 0.25);
	m_targetSprites.setOrigin(20, 20);
	*/
	
	//m_tankSprite.setPosition(m_level.m_tank.m_position);
	//m_tankSprite.setScale(m_level.m_tank.m_scale);
	//m_tankSprite.setOrigin(123, 57);
	//m_tankSprite.rotate(90);
	//m_tankSprite.setRotation(90);
	//m_tankSprite.setTextureRect(sf::IntRect(0, 95, 246, 114));
	//m_turretSprite.setTexture(texture);
	//m_turretSprite.setPosition(m_level.m_tank.m_position);
	//m_turretSprite.setScale(m_level.m_tank.m_scale);
	//m_turretSprite.setOrigin(95.5f, 47);
	//m_turretSprite.rotate(90);
	//m_turretSprite.setRotation(90);
	//m_turretSprite.setTextureRect(sf::IntRect(247, 0, 191, 94)); // Further into the top left corner


	//Because we set the origin of the sprite from the top left to the centre of the sprite it moved slightly off screen with the coords we put in to set the position of the sprite
	//The tank rotated clockwise
	//Rotate adds to current rotation where as set rotation sets the rotation to one value 

	//m_holder.release("tankAtlas"); // The sprites have become white cubes 

#ifdef TEST_FPS
	x_updateFPS.setFont(m_arialFont);
	x_updateFPS.setPosition(20, 300);
	x_updateFPS.setCharacterSize(24);
	x_updateFPS.setFillColor(sf::Color::White);
	x_drawFPS.setFont(m_arialFont);
	x_drawFPS.setPosition(20, 350);
	x_drawFPS.setCharacterSize(24);
	x_drawFPS.setFillColor(sf::Color::White);
#endif
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame.asMilliseconds()); //60 fps
#ifdef TEST_FPS
			x_secondTime += timePerFrame;
			x_updateFrameCount++;
			if (x_secondTime.asSeconds() > 1)
			{
				std::string updatesPS = "UPS " + std::to_string(x_updateFrameCount - 1);
				x_updateFPS.setString(updatesPS);
				std::string drawsPS = "DPS " + std::to_string(x_drawFrameCount);
				x_drawFPS.setString(drawsPS);
				x_updateFrameCount = 0;
				x_drawFrameCount = 0;
				x_secondTime = sf::Time::Zero;
			}
#endif
		}
		render(); // as many as possible
#ifdef TEST_FPS
		x_drawFrameCount++;
#endif
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	m_tank.update(dt);
	m_timer.setString("Time: " + std::to_string(60 - timercount));
	accuracy.setString("Accurcy: " + std::to_string(percentagehit) + "%");
	score.setString("Score: " + std::to_string(scorecount));
	endtext.setString("GameOver \n Score was " + std::to_string(scorecount) + "\n and Accuracy was " + std::to_string(percentagehit) + "%");

	m_targetSprite[activetarget].setScale(m_targetSprite[activetarget].getScale().x - 0.0005, m_targetSprite[activetarget].getScale().y - 0.0005);
	
	if (m_targetSprite[activetarget].getScale().x <= 0.05)
	{
		activetarget++;
	}
	if (activetarget == 7)
	{
		gameover = true;
		activetarget = 0;
	}

	//for (auto const& target : m_level.m_target)
	//{
		//if (m_targetSprite[activetarget].getPosition() == target.m_position)
		//{
			if (m_tank.checkTargetCollision() == true)
			{
				scorecount++;
				activetarget++;
			}
		//}
	//}
	if (m_tank.gettotalshots() >= 1)
	{
		percentagehit = ((m_tank.getshotshit() / m_tank.gettotalshots()) * 100) / 2;
	}
	

	count = time.getElapsedTime();
	timercount = count.asSeconds();

	if (60 - timercount <= 0)
	{
		gameover = true;
	}
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	if (gameover == false)
	{
		m_window.draw(m_bgSprite);
		m_window.draw(m_timer);
		m_window.draw(accuracy);
		m_window.draw(score);
	for (sf::Sprite& wall : m_wallSprites)
	{
		m_window.draw(wall);
	}	
	m_window.draw(m_targetSprite[activetarget]);
	m_tank.render(m_window);
	}
	if (gameover == true)
	{
		m_window.clear();
		m_window.draw(endtext);
	}
	
#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}





