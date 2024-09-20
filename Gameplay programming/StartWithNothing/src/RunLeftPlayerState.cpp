#include <Events.h>

#include <RunLeftPlayerState.h>

#include <AttackPlayerState.h>
#include <ClubPlayerState.h>
#include <ShieldPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* RunLeftPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> AttackPlayerState");
		return new AttackPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::CLUB_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> ClubPlayerState");
		return new ClubPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::SHIELD_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> ShieldPlayerState");
		return new ShieldPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_WALL_EVENT || input.getCurrent() == gpp::Events::Event::RUN_LEFT_STOP_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunLeftPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void RunLeftPlayerState::update(Player& player) {
	DEBUG_MSG("RunLeftPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(32);
	player.moveLeft();
}
void RunLeftPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunLeftPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(64, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(128, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(192, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(256, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(448, 576, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(512, 576, 64, 64));

	player.getAnimatedSpriteFrame().setTime(seconds(0.05f));
}
void RunLeftPlayerState::exit(Player& player) 
{
	DEBUG_MSG("Exiting RunLeftPlayerState");
	DEBUG_MSG(typeid(player).name());
}