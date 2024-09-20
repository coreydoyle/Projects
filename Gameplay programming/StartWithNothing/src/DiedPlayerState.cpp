#include <Events.h>

#include <DiedPlayerState.h>

#include <RevivedPlayerState.h>

PlayerState *DiedPlayerState::handleInput(gpp::Events &input)
{
	if (input.getCurrent() == gpp::Events::Event::REVIVED_EVENT)
	{
		DEBUG_MSG("DiedPlayerState -> RevivedPlayerState");
		return new RevivedPlayerState();
	}
	return nullptr;
}
void DiedPlayerState::update(Player &player)
{
	DEBUG_MSG("DiedPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	player.setOrigin(32);
}
void DiedPlayerState::enter(Player &player)
{
	DEBUG_MSG("Entering DiedPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(false);

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 1280, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(64, 1280, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(128, 1280, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(256, 1280, 64, 64));
	player.getAnimatedSprite().addFrame(sf::IntRect(320, 1280, 64, 64));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void DiedPlayerState::exit(Player &player)
{
	DEBUG_MSG("Exiting DiedPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}