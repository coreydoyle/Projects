#include "Game.h"
#include <iostream>

// Our target FPS
static double const FPS{ 60.0f };

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
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

	m_holder.acquire("tankAtlas", thor::Resources::fromFile<sf::Texture>("resources/images/spritesheet.png"));
	sf::Texture& texture = m_holder["tankAtlas"];

	m_tankSprite.setTexture(texture);
	m_tankSprite.setPosition(250, 450);
	m_tankSprite.setOrigin(123, 57);
	m_tankSprite.rotate(90);
	m_tankSprite.setRotation(90);
	m_tankSprite.setTextureRect(sf::IntRect(0, 95, 246, 114));
	m_turretSprite.setTexture(texture);
	m_turretSprite.setPosition(250, 450);
	m_turretSprite.setOrigin(95.5f, 47);
	m_turretSprite.rotate(90);
	m_turretSprite.setRotation(90);
	m_turretSprite.setTextureRect(sf::IntRect(247, 0, 191, 94)); // Further into the top left corner
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
		case sf::Keyboard::Up:
			// Up key was pressed...
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_tankSprite);
	m_window.draw(m_turretSprite);
#ifdef TEST_FPS
	m_window.draw(x_updateFPS);
	m_window.draw(x_drawFPS);
#endif
	m_window.display();
}





