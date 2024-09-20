#include <Events.h>

#include <AttackPlayerState.h>

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* AttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::ATTACK_STOP_EVENT)
	{
		DEBUG_MSG("AttackPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("AttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void AttackPlayerState::update(Player& player) {
	DEBUG_MSG("AttackPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(96);
}

void AttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering AttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 2672, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(192, 2672, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 2672, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(576, 2672, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(768, 2672, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(960, 2672, 192, 192));

	player.getAnimatedSprite().setTime(seconds(0.1f));
}
void AttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting AttackPlayerState");
	DEBUG_MSG(typeid(player).name());
}