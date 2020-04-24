#include "RightCommand.h"
#include "../GameObjects/Player/PlayerMovement.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Containers/PointerIncludes.cpp"

#include <cassert>

namespace Game::Commands
{
	void RightCommand::Execute(Containers::SmartPtr<Core::BaseComponents::Node> i_node)
	{
		Containers::WeakPtr<GameObjects::Player::PlayerMovement> playerMovement =
			i_node->GetComponent<GameObjects::Player::PlayerMovement>();

		assert(playerMovement);
		playerMovement.Lock()->MoveRight();
	}
}
