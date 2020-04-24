#pragma once
#include "Command.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Node.h"

namespace Game::Commands
{
	class RightCommand : public Command
	{
	public:
		void Execute(Containers::SmartPtr<Core::BaseComponents::Node> i_node) override;
	};
}
