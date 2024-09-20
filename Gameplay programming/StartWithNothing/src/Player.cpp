#include <Player.h>
#include <iostream>
#include <string>

Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Player::~Player()
{
	DEBUG_MSG("~Player()");
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update() {
	m_animated_sprite.update();
	m_state->update(*this);
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }

void Player::setPosition(int t_x,int t_y) {
	position.x = t_x;
	position.y = t_y;
	m_animated_sprite.setPosition(position);
}

void Player::setOrigin(int x) {
	m_animated_sprite.setOrigin(x,x);
}

void Player::moveRight() {
	position = m_animated_sprite.getPosition();
	position.x += 0.5f;
	m_animated_sprite.setPosition(position);
}

void Player::moveLeft() {
	position = m_animated_sprite.getPosition();
	position.x -= 0.5f;
	m_animated_sprite.setPosition(position);
}

void Player::setHealth(int t_health)
{
	health = t_health;
}

int Player::getHealth() 
{
	return health;
}

void Player::setPlayerText() {
	player_text.setFont(font);
	player_text.setString("Orc health: " + std::to_string(health));
	player_text.setPosition(0,25);
	player_text.setFillColor(sf::Color::White);
	player_text.setOutlineColor(sf::Color::Black);
	player_text.setOutlineThickness(5);
	player_text.setCharacterSize(20U);
}

void Player::setNpcText() {
	npc_text.setFont(font);
	npc_text.setString("Troll health: " + std::to_string(health));
	npc_text.setPosition(620,25);
	npc_text.setFillColor(sf::Color::White);
	npc_text.setOutlineColor(sf::Color::Black);
	npc_text.setOutlineThickness(5);
	npc_text.setCharacterSize(20U);
}

sf::Text Player::getPlayerText() {
	return player_text;
}

sf::Text Player::getNpcText() {
	return npc_text;
}

void Player::setFont() {

	if (!font.loadFromFile("./assets/ariblk.ttf"))
	{
		DEBUG_MSG("Failed to load file");
	}
}

void Player::damageHealth(int t_damage) {
	health -= t_damage;
	if(health <= 0 )
	{
		health = 0;
	}
}

void Player::setDamage(int t_damage) {
	damage = t_damage;
}

int Player::getDamage() {
	return damage;
}




