#include <./include/Game.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define CUTE_C2_IMPLEMENTATION
#include <./include/cute_c2.h>

sf::RenderWindow* window = new RenderWindow(sf::VideoMode(800, 600), "Launching...");

// Rectangle setup
sf::Texture player_texture;
sf::Texture npc_texture;

sf::Sprite player_sprite;
sf::Sprite npc_sprite;

sf::Color playerColour = sf::Color::White;
sf::Color npcColour = sf::Color::White;

// Circle setup
sf::CircleShape player_circle;
sf::CircleShape npc_circle;

// Capsules setup
sf::CircleShape player_capsule_start;
sf::CircleShape player_capsule_end;
sf::RectangleShape player_capsule_mid;

sf::CircleShape npc_capsule_start;
sf::CircleShape npc_capsule_end;
sf::RectangleShape npc_capsule_mid;

Game::Game(){}

void Game::initialize()
{
	player = new Player();
	npc = new NPC();

	window->setSize(sf::Vector2u(640, 480));
	window->setTitle("Game");

	player->x = 0;
	player->y = 0;
	player->w = 0;
	player->h = 0;
	player->r = 0;

	npc->x = 0;
	npc->y = 0;
	npc->w = 0;
	npc->h = 0;
	npc->r = 0;

	player_texture.loadFromFile(".//images//player//Player.png");
	npc_texture.loadFromFile(".//images//npc//npc.png");

	player_sprite.setTexture(player_texture);
	npc_sprite.setTexture(npc_texture);

	player_circle.setRadius(50.0f);
	player_circle.setFillColor(sf::Color::White);
	player_circle.setPosition(400.0f,200.0f);
	player_circle.setOrigin(50.0f, 50.0f);

	npc_circle.setRadius(50.0f);
	npc_circle.setFillColor(sf::Color::White);
	npc_circle.setPosition(250.0f,200.0f);
	npc_circle.setOrigin(50.0f, 50.0f);

	player_capsule_start.setRadius(40.0f);
	player_capsule_start.setFillColor(sf::Color::White);
	player_capsule_start.setPosition(200,300);
	player_capsule_start.setOrigin(40.0f,40.0f);

	player_capsule_end.setRadius(40.0f);
	player_capsule_end.setFillColor(sf::Color::White);
	player_capsule_end.setPosition(280,300);
	player_capsule_end.setOrigin(40.0f,40.0f);

	player_capsule_mid.setSize(sf::Vector2f(80.0f,80.0f));
	player_capsule_mid.setFillColor(sf::Color::White);
	player_capsule_mid.setPosition(240,300);
	player_capsule_mid.setOrigin(40.0f,40.0f);

	npc_capsule_start.setRadius(40.0f);
	npc_capsule_start.setFillColor(sf::Color::White);
	npc_capsule_start.setPosition(300,400);
	npc_capsule_start.setOrigin(40.0f,40.0f);

	npc_capsule_end.setRadius(40.0f);
	npc_capsule_end.setFillColor(sf::Color::White);
	npc_capsule_end.setPosition(380,400);
	npc_capsule_end.setOrigin(40.0f,40.0f);

	npc_capsule_mid.setSize(sf::Vector2f(80.0f,80.0f));
	npc_capsule_mid.setFillColor(sf::Color::White);
	npc_capsule_mid.setPosition(340,400);
	npc_capsule_mid.setOrigin(40.0f,40.0f);
}

void Game::run()
{
	initialize();

	while (window->isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		player->update();
		npc->update();

		//Setup NPC AABB
		c2AABB aabb_npc;
		aabb_npc.min = c2V(npc_sprite.getPosition().x, npc_sprite.getPosition().y);
		aabb_npc.max = c2V(
			npc_sprite.getPosition().x +
			npc_sprite.getGlobalBounds().width, 
			npc_sprite.getPosition().y +
			npc_sprite.getGlobalBounds().height);
			
		//Setup Player AABB
		c2AABB aabb_player;
		aabb_player.min = c2V(player_sprite.getPosition().x,player_sprite.getPosition().y);
		aabb_player.max = c2V(player_sprite.getPosition().x + player_sprite.getGlobalBounds().width, player_sprite.getPosition().y + player_sprite.getGlobalBounds().height);

		if(c2AABBtoAABB(aabb_npc, aabb_player)){
			cout << "NPC and Player are in Collision" << endl;
			player_sprite.setColor(sf::Color::Red);
            npc_sprite.setColor(sf::Color::Green);
		} else{
			cout << "No Collision" << endl; 
			player_sprite.setColor(playerColour);
            npc_sprite.setColor(npcColour);
		}

		//Player circle
		c2Circle circle_player;
		circle_player.p = c2V(player_circle.getPosition().x, player_circle.getPosition().y);
		circle_player.r = player_circle.getRadius();
		
		//setup NPC Circle
		c2Circle circle_npc;
		circle_npc.p = c2V(npc_circle.getPosition().x, npc_circle.getPosition().y);
		circle_npc.r = npc_circle.getRadius();

		if(c2CircletoCircle(circle_player, circle_npc)) {
			cout << "Player and Npc in Collision" << endl;
			player_circle.setFillColor(sf::Color::Cyan);
			npc_circle.setFillColor(sf::Color::Yellow);
		}
		else {
			cout << "No Collision" << endl;
			player_circle.setFillColor(sf::Color::White);
			npc_circle.setFillColor(sf::Color::White);
		}

		//Capsule Setup
		c2Capsule capsule_player;
		capsule_player.a = c2V(player_capsule_start.getPosition().x, player_capsule_start.getPosition().y);
		capsule_player.b = c2V(player_capsule_end.getPosition().x, player_capsule_end.getPosition().y);
		capsule_player.r = player_capsule_start.getRadius();

		if(c2CircletoCapsule(circle_npc, capsule_player)) {
			cout << "Player and Npc in Collision" << endl;
			npc_circle.setFillColor(sf::Color::Yellow);
			player_capsule_start.setFillColor(sf::Color::Red);
			player_capsule_mid.setFillColor(sf::Color::Red);
			player_capsule_end.setFillColor(sf::Color::Red);
		}
		else {
			cout << "No Collision" << endl;
			player_capsule_start.setFillColor(sf::Color::White);
			player_capsule_mid.setFillColor(sf::Color::White);
			player_capsule_end.setFillColor(sf::Color::White);
		}
		
		if(c2AABBtoCapsule(aabb_npc,capsule_player)) {
			cout << "Player and Npc in Collision" << endl;
			npc_sprite.setColor(sf::Color::Green);
			player_capsule_start.setFillColor(sf::Color::Red);
			player_capsule_mid.setFillColor(sf::Color::Red);
			player_capsule_end.setFillColor(sf::Color::Red);
		}
		else {
			cout << "No Collision" << endl;
		}

		c2Capsule capsule_npc;
		capsule_npc.a = c2V(npc_capsule_start.getPosition().x, npc_capsule_start.getPosition().y);
		capsule_npc.b = c2V(npc_capsule_end.getPosition().x, npc_capsule_end.getPosition().y);
		capsule_npc.r = npc_capsule_start.getRadius();

		if(c2AABBtoCapsule(aabb_player,capsule_npc)) {
			cout << "Player and Npc in Collision" << endl;
		 	player_sprite.setColor(sf::Color::Red);
			npc_capsule_start.setFillColor(sf::Color::Green);
			npc_capsule_mid.setFillColor(sf::Color::Green);
			npc_capsule_end.setFillColor(sf::Color::Green);
		}
		else {
			cout << "No Collision" << endl;
			npc_capsule_start.setFillColor(sf::Color::White);
			npc_capsule_mid.setFillColor(sf::Color::White);
			npc_capsule_end.setFillColor(sf::Color::White);
		}

		if(c2CircletoAABB(circle_npc,aabb_player)) {
			cout << "Player and Npc in Collision" << endl;
			player_sprite.setColor(sf::Color::Red);
			npc_circle.setFillColor(sf::Color::Yellow);
		}
		else {
			cout << "No Collision" << endl;
		}
		 
            
       
           

		// Move the player
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::W)
			{
				player_sprite.move(sf::Vector2f(0.0f, -4.0f));
				player_circle.move(sf::Vector2f(0.0f, -4.0f));
				player_capsule_start.move(sf::Vector2f(0.0f, -4.0f));
				player_capsule_mid.move(sf::Vector2f(0.0f, -4.0f));
				player_capsule_end.move(sf::Vector2f(0.0f, -4.0f));
			}
			if(event.key.code == sf::Keyboard::S)
			{
				player_sprite.move(sf::Vector2f(0.0f, 4.0f));
				player_circle.move(sf::Vector2f(0.0f, 4.0f));
				player_capsule_start.move(sf::Vector2f(0.0f, 4.0f));
				player_capsule_mid.move(sf::Vector2f(0.0f, 4.0f));
				player_capsule_end.move(sf::Vector2f(0.0f, 4.0f));
			}
			if(event.key.code == sf::Keyboard::A)
			{
				player_sprite.move(sf::Vector2f(-4.0f, 0.0f));
				player_circle.move(sf::Vector2f(-4.0f, 0.0f));
				player_capsule_start.move(sf::Vector2f(-4.0f, 0.0f));
				player_capsule_mid.move(sf::Vector2f(-4.0f, 0.0f));
				player_capsule_end.move(sf::Vector2f(-4.0f, 0.0f));
			}
			if(event.key.code == sf::Keyboard::D)
			{
				player_sprite.move(sf::Vector2f(4.0f, 0.0f));
				player_circle.move(sf::Vector2f(4.0f, 0.0f));
				player_capsule_start.move(sf::Vector2f(4.0f, 0.0f));
				player_capsule_mid.move(sf::Vector2f(4.0f, 0.0f));
				player_capsule_end.move(sf::Vector2f(4.0f, 0.0f));
			}
		}
	}

}

void Game::draw()
{
	window->clear();
	window->draw(npc_sprite);
	window->draw(player_sprite);


	window->draw(npc_circle);
	window->draw(player_circle);


	window->draw(player_capsule_start);
	window->draw(player_capsule_mid);
	window->draw(player_capsule_end);
	window->draw(npc_capsule_start);
	window->draw(npc_capsule_mid);
	window->draw(npc_capsule_end);


	window->display();
}


