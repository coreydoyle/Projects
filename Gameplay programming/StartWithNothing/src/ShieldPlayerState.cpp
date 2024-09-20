#include <Events.h>

#include <ShieldPlayerState.h>

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* ShieldPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("ShieldPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::SHIELD_STOP_EVENT)
	{
		DEBUG_MSG("ShieldPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("ShieldPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void ShieldPlayerState::update(Player& player) {
	DEBUG_MSG("ShieldPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(32);
}

void ShieldPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering ShieldPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(576, 704, 64, 64));
	// player.getAnimatedSprite().addFrame(sf::IntRect(640, 704, 64, 64));
	// player.getAnimatedSprite().addFrame(sf::IntRect(704, 704, 64, 64));
	// player.getAnimatedSprite().addFrame(sf::IntRect(768, 704, 64, 64));
	// player.getAnimatedSprite().addFrame(sf::IntRect(832, 704, 64, 64));
	// player.getAnimatedSprite().addFrame(sf::IntRect(896, 704, 64, 64));

	player.getAnimatedSprite().setTime(seconds(0.1f));
}
void ShieldPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting ShieldPlayerState");
	DEBUG_MSG(typeid(player).name());
}