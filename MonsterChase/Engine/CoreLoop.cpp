#include "CoreLoop.h"
#include <SFML/Graphics.hpp>
#include "GameObjectUpdater.h"

namespace Core
{
	namespace Controllers
	{
		CoreLoop::CoreLoop()
		= default;

		CoreLoop::~CoreLoop()
		{
			delete _clock;
			delete _gameObjectUpdater;
		}

		sf::RenderWindow* CoreLoop::Setup(const int windowWidth, const int windowHeight, const std::string& windowTitle)
		{
			this->_gameObjectUpdater = new GameObjectUpdater();

			this->_windowContext = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle);
			this->_clock = new sf::Clock();

			return this->_windowContext;
		}

		void CoreLoop::Run() const
		{
			const sf::Time elapsedTime = this->_clock->restart();
			_gameObjectUpdater->Process(elapsedTime.asSeconds());
		}
	}
}
