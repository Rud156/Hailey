#include "InputHandler.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "ForwardCommand.h"
#include "BackwardCommand.h"
#include "ShootCommand.h"
#include "Command.h"

#include <SFML/Graphics.hpp>

namespace Game::Commands
{
	InputHandler::InputHandler()
	{
		this->_leftCommand = new LeftCommand();
		this->_rightCommand = new RightCommand();
		this->_forwardCommand = new ForwardCommand();
		this->_backwardCommand = new BackwardCommand();
		this->_shootCommand = new ShootCommand();
	}

	InputHandler::~InputHandler()
	{
		delete this->_leftCommand;
		delete this->_rightCommand;
		delete this->_forwardCommand;
		delete this->_backwardCommand;
		delete this->_shootCommand;
	}

	std::vector<Command*> InputHandler::CollectCommands(float) const
	{
		std::vector<Command*> activeCommands;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			activeCommands.push_back(this->_leftCommand);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			activeCommands.push_back(this->_rightCommand);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			activeCommands.push_back(this->_forwardCommand);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			activeCommands.push_back(this->_backwardCommand);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			activeCommands.push_back(this->_shootCommand);
		}

		return activeCommands;
	}
}
