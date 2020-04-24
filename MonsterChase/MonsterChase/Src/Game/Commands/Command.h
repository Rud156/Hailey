#pragma once
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Node.h"

namespace Game::Commands
{
	class Command
	{
	public:
		virtual ~Command();
		virtual void Execute(Containers::SmartPtr<Core::BaseComponents::Node> i_node) = 0;
	};
}
