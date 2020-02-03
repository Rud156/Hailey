#include "CoreLoop.h"
#include "GameObjectUpdater.h"
#include <SFML/Graphics.hpp>

namespace Core
{
	namespace Controllers
	{
		CoreLoop::CoreLoop() = default;

		CoreLoop::~CoreLoop()
		{
			delete this->_clock;
			delete this->_window;
			delete this->_gameObjectUpdater;
		}

		void CoreLoop::Setup(sf::RenderWindow* window)
		{
			this->_gameObjectUpdater = new GameObjectUpdater();
			this->_clock = new sf::Clock();
			this->_window = window;
		}

		void CoreLoop::Run() const
		{
			const sf::Time elapsedTime = this->_clock->restart();
			_gameObjectUpdater->Process(elapsedTime.asSeconds());
			_gameObjectUpdater->Render(this->_window);
		}
	}
}
