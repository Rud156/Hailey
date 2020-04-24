#include "ShootCommand.h"

#include "../GameObjects/Player/PlayerShooting.h"
#include "Src/Containers/PointerIncludes.cpp"

namespace Game::Commands
{
	void ShootCommand::Execute(Containers::SmartPtr<Core::BaseComponents::Node> i_node)
	{
		Containers::WeakPtr<GameObjects::Player::PlayerShooting> playerShooting =
			i_node->GetComponent<GameObjects::Player::PlayerShooting>();

		assert(playerShooting);
		playerShooting.Lock()->Shoot();
	}
}
