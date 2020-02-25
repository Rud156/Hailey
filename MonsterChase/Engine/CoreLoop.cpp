#include "CoreLoop.h"
#include "GameObjectUpdater.h"
#include "LoopTimer.h"
#include <SFML/Graphics.hpp>

namespace Core::Controllers
{
	CoreLoop::CoreLoop() = default;

	CoreLoop::~CoreLoop()
	{
		delete this->_loopTimer;
		delete this->_window;
		delete this->_gameObjectUpdater;
	}

	void CoreLoop::Setup(sf::RenderWindow* i_window)
	{
		this->_gameObjectUpdater = new GameObjectUpdater();
		this->_loopTimer = new LoopTimer();
		this->_window = i_window;
	}

	void CoreLoop::Run() const
	{
		const auto elapsedTime = static_cast<float>(this->_loopTimer->RestartClock());
		_gameObjectUpdater->Process(elapsedTime);
		_gameObjectUpdater->Render(this->_window);
	}
}
