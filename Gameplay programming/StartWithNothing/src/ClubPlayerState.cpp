#include <Events.h>

#include <ClubPlayerState.h>

#include <RunRightPlayerState.h>
#include <IdlePlayerState.h>
#include <DiedPlayerState.h>

PlayerState* ClubPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("ClubPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::CLUB_STOP_EVENT)
	{
		DEBUG_MSG("ClubPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("ClubPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void ClubPlayerState::update(Player& player) {
	DEBUG_MSG("ClubPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(96);
}

void ClubPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering ClubPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 1920, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(192, 1920, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(384, 1920, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(576, 1920, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(768, 1920, 192, 192));
	player.getAnimatedSprite().addFrame(sf::IntRect(960, 1920, 192, 192));

	player.getAnimatedSprite().setTime(seconds(0.05f));
}
void ClubPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting ClubPlayerState");
	DEBUG_MSG(typeid(player).name());
}