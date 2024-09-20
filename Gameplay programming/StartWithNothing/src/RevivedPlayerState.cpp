#include <Events.h>

#include <RevivedPlayerState.h>

#include <DiedPlayerState.h>
#include <IdlePlayerState.h>

PlayerState* RevivedPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT)
	{
		DEBUG_MSG("RevivedPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void RevivedPlayerState::update(Player& player) {
	// Switch from RevivedPlayerState to IdlePlayerState
	DEBUG_MSG("RevivedPlayerState -> IdlePlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 0.5f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new IdlePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
	player.setOrigin(32);
}
void RevivedPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RevivedPlayerState");

	// How long in State Clock
	this->m_clock.restart();

	// Clear existing frames
	player.getAnimatedSprite().clearFrames();

	// Set animation control members
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(false);

	// Add animation frames
	player.getAnimatedSprite().addFrame(sf::IntRect(448, 128, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 128, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 128, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(256, 128, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(128, 128, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(64, 128, 64, 64));
	
	// Set the animation time
	player.getAnimatedSprite().setTime(seconds(0.1f));
}
void RevivedPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting RevivedPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}