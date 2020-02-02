#include "CoreLoop.h"
#include <SFML/Graphics.hpp>
#include "GameObjectUpdater.h"

namespace Core
{
	namespace Controllers
	{
		CoreLoop::CoreLoop() = default;

		CoreLoop::~CoreLoop()
		{
			delete _clock;
			delete _gameObjectUpdater;
		}

		void CoreLoop::Setup()
		{
			this->_gameObjectUpdater = new GameObjectUpdater();
			this->_clock = new sf::Clock();
		}

		void CoreLoop::Run() const
		{
			const sf::Time elapsedTime = this->_clock->restart();
			_gameObjectUpdater->Process(elapsedTime.asSeconds());
		}
	}
}
