#pragma once
#include "Command.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Containers/SmartPtr.h"

namespace Game::Commands
{
	class ShootCommand : public Command
	{
	public:
		void Execute(Containers::SmartPtr<Core::BaseComponents::Node> i_node) override;
	};
}
