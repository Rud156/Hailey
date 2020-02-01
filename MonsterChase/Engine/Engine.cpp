#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "CoreLoop.h"
#include <iostream>

namespace Engine
{
	Engine::Engine() = default;

	Engine::~Engine() = default;

	sf::RenderWindow* Engine::Init(const int windowWidth, const int windowHeight, const std::string& windowTitle)
	{
		std::cout << "Engine Initialized" << std::endl;

		_coreLoop = new Core::Controllers::CoreLoop();
		return _coreLoop->Setup(windowWidth, windowHeight, windowTitle);
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
