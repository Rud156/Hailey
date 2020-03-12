#include "Engine.h"
#include "Core/Controllers/CoreLoop.h"

#include <iostream>

namespace Engine
{
	Engine::Engine() = default;

	Engine::~Engine() = default;

	void Engine::Init(sf::RenderWindow* i_window)
	{
		std::cout << "Engine Initialized" << std::endl;

		_coreLoop = new Core::Controllers::CoreLoop();
		_coreLoop->Setup(i_window);
	}

	void Engine::Run() const
	{
		_coreLoop->Run();
	}

	void Engine::ShutDown() const
	{
		std::cout << "Engine ShutDown" << std::endl;

		delete _coreLoop;
	}
}
