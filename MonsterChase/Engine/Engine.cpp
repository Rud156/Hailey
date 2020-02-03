#include "stdafx.h"
#include "Engine.h"
#include "CoreLoop.h"
#include <iostream>

namespace Engine
{
	Engine::Engine() = default;

	Engine::~Engine() = default;

	void Engine::Init(sf::RenderWindow* window)
	{
		std::cout << "Engine Initialized" << std::endl;

		_coreLoop = new Core::Controllers::CoreLoop();
		_coreLoop->Setup(window);
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
