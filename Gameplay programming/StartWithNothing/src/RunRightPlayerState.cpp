#include <Events.h>

#include <RunRightPlayerState.h>

#include <AttackPlayerState.h>
#include <ClubPlayerState.h>
#include <ShieldPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>
#include <RunLeftPlayerState.h>

PlayerState* RunRightPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("RunRightPlayerState -> AttackPlayerState");
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
	else if (input.getCurrent() == gpp::Events::Event::HIT_WALL_EVENT || input.getCurrent() == gpp::Events::Event::RUN_RIGHT_STOP_EVENT)
	{
		DEBUG_MSG("RunRightPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunRightPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::RUN_LEFT_START_EVENT) {
		DEBUG_MSG("RunRightPlayerState -> RunLeftPlayerState");
		return new RunLeftPlayerState();
	}
	return nullptr;
}
void RunRightPlayerState::update(Player& player) {
	DEBUG_MSG("RunRightPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(32);
	player.moveRight();
}
void RunRightPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunRightPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(64, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(128, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(192, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(256, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(448, 704, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(512, 704, 64, 64));

	player.getAnimatedSpriteFrame().setTime(seconds(0.05f));
}
void RunRightPlayerState::exit(Player& player) 
{
	DEBUG_MSG("Exiting RunRightPlayerState");
	DEBUG_MSG(typeid(player).name());
}