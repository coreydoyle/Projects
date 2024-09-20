#ifndef PLAYER_H
#define PLAYER_H
#include <Events.h>
#include <PlayerState.h>
#include <AnimatedSprite.h>
#include <stdio.h>
#include <IdlePlayerState.h>
#include <vector>
#include <SFML/Graphics.hpp>

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	sf::Vector2f position;
	int health;
	sf::Text player_text;
	sf::Text npc_text;
	sf::Font font;
	int damage;
	// sf::circleShape weapon_circle;
	// sf::circleShape enemy_circle;
public:
	Player(const AnimatedSprite&);
	~Player();
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void setPosition(int t_x, int t_y);
	void setOrigin(int x);
	void moveRight();
	void moveLeft();
	void setHealth(int t_health);
	int getHealth();
	sf::Text getPlayerText();
	sf::Text getNpcText();
	void setPlayerText();
	void setNpcText();
	void setFont();
	void setDamage(int t_damage);
	int getDamage();
	void damageHealth(int t_damage);
	// sf::circleShape getWeaponCircle();
};
#endif

