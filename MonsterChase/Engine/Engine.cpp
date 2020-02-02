#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "CoreLoop.h"
#include <iostream>

namespace Engine
{
	Engine::Engine() = default;

	Engine::~Engine() = default;

	void Engine::Init()
	{
		std::cout << "Engine Initialized" << std::endl;

		_coreLoop = new Core::Controllers::CoreLoop();
		_coreLoop->Setup();
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
