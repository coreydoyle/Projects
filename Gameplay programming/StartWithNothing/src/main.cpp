#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Events.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Player Finite State Machine");

	// Load a sprite to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}

	sf::Texture npc_texture;
	if(!npc_texture.loadFromFile(ENEMY_SPRITES))
	{
		DEBUG_MSG("Failed to load file");
		if(!npc_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}

	sf::Texture background_texture;
	sf::Sprite background_sprite;
	if(!background_texture.loadFromFile("./assets/background.png"))
	{
		DEBUG_MSG("Failed to load file");
		if(!background_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}
	background_sprite.setTexture(background_texture);
	background_sprite.setScale(1.25,1.5);

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	player_animated_sprite.setScale(2,2);

	AnimatedSprite npc_animated_sprite(npc_texture);
	npc_animated_sprite.setScale(-2,2);

	Player player(player_animated_sprite);
	Player npc(npc_animated_sprite);

	player.setPosition(50,520);
	player.setHealth(100);
	

	npc.setPosition(600,520);
	npc.setHealth(100);
	

	gpp::Events input;
	gpp::Events ai;

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				// Died Event
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
					input.setCurrent(gpp::Events::Event::DIED_EVENT);
				}
				// Revieved Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
					input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
					ai.setCurrent(gpp::Events::Event::REVIVED_EVENT);
					player.setHealth(100);
					player.setPosition(50,520);
					npc.setHealth(100);
				}
				// Attack
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
					player.setDamage(10);
					npc.damageHealth(player.getDamage());
				}
				//Club Attack
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					DEBUG_MSG("gpp::Events::Event::CLUB_START_EVENT");
					input.setCurrent(gpp::Events::Event::CLUB_START_EVENT);
					player.setDamage(5);
					npc.damageHealth(player.getDamage());
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					DEBUG_MSG("gpp::Events::Event::SHIELD_START_EVENT");
					input.setCurrent(gpp::Events::Event::SHIELD_START_EVENT);
				}
				//Run Right
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_LEFT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_LEFT_START_EVENT);
				}
				break;

				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				// Stop Attack
				if (event.key.code == sf::Keyboard::Z)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				}
				else if (event.key.code == sf::Keyboard::X)
				{
					DEBUG_MSG("gpp::Events::Event::CLUB_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::CLUB_STOP_EVENT);
				}
				else if (event.key.code == sf::Keyboard::C)
				{
					DEBUG_MSG("gpp::Events::Event::SHIELD_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::SHIELD_STOP_EVENT);
				}
				// Stop Running Right
				else if (event.key.code == sf::Keyboard::D)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_LEFT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_LEFT_STOP_EVENT);
				}
				break;

			default:
				DEBUG_MSG("gpp::Events::Event::NONE");
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);

			if (npc.getHealth() <= 0)
			{
					ai.setCurrent(gpp::Events::Event::DIED_EVENT);
			}
			npc.handleInput(ai);
		}

	player.setPlayerText();
	player.setFont();

	npc.setNpcText();
	npc.setFont();
	
		// Update AI
		ai.setCurrent(gpp::Events::Event::NONE);
		npc.handleInput(ai);

		// Update the Player
		player.update();
		
		//Update the NPC
		npc.update();

		// Clear screen
		window.clear();

		//Draw background
		window.draw(background_sprite);

		//Text
		window.draw(player.getPlayerText());
		window.draw(npc.getNpcText());

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSpriteFrame());

		// Draw the NPC's Current Animated Sprite
		window.draw(npc.getAnimatedSpriteFrame());
		
		

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};