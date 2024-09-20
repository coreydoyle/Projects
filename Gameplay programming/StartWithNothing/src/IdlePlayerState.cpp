#include <Events.h>

#include <IdlePlayerState.h>

#include <AttackPlayerState.h>
#include <ClubPlayerState.h>
#include <ShieldPlayerState.h>
#include <RunRightPlayerState.h>
#include <DiedPlayerState.h>
#include <RunLeftPlayerState.h>


PlayerState* IdlePlayerState::handleInput(gpp::Events& input) {

	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> AttackPlayerState");
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
	else if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT) {
		DEBUG_MSG("IdlePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::RUN_LEFT_START_EVENT) {
		DEBUG_MSG("IdlePlayerState -> RunLeftPlayerState");
		return new RunLeftPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("IdlePlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}

void IdlePlayerState::update(Player& player) {
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(32);
}

void IdlePlayerState::enter(Player& player) 
{
	DEBUG_MSG("Entering IdlePlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(64, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(128, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(192, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(256, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 448, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(448, 448, 64, 64));
	
	player.getAnimatedSprite().setTime(seconds(0.1f));
}

void IdlePlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting IdlePlayerState");
	DEBUG_MSG(typeid(player).name());
}