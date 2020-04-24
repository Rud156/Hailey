#pragma once
#include <vector>

namespace Game::Commands
{
	class Command;
	class LeftCommand;
	class RightCommand;
	class ForwardCommand;
	class BackwardCommand;
	class ShootCommand;

	class InputHandler
	{
	private:
		LeftCommand* _leftCommand;
		RightCommand* _rightCommand;
		ForwardCommand* _forwardCommand;
		BackwardCommand* _backwardCommand;
		ShootCommand* _shootCommand;

	public:
		InputHandler();
		~InputHandler();

		[[nodiscard]] std::vector<Command*> CollectCommands(float i_deltaTime) const;
	};
}
