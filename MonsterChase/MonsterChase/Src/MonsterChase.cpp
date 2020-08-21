// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Core/Loaders/JsonGOLoader.h"
#include "Src/Engine.h"
#include "Src/Memory/MemorySystem.h"
#include "Src/Utils/Debug.h"
#include "Src/Utils/Random.h"
#include "Src/Containers/SmartPtr.h"
#include <SFML/Graphics.hpp>

#include "Src/Memory/Allocators.h"
#include "Game/GameMain.h"

#include <conio.h>
#include <cassert>
#include <iostream>
#include <Windows.h>

#pragma region RunBeforeMain

// Super Hacky But Works
class RunBeforeMain
{
public:
	~RunBeforeMain()
	{
		Utils::Debug::LogOutputToWindow("Memory Manager Cleared");
		Memory::MemorySystem::destroy();
	}
};

RunBeforeMain runBeforeMain;

#pragma endregion

LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Quit when we close the main window
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

INT WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, int)
{
	{
		// Define a class for our main window
		WNDCLASS windowClass;
		windowClass.style = 0;
		windowClass.lpfnWndProc = &onEvent;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = nullptr;
		windowClass.hCursor = nullptr;
		windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = TEXT("SFML App");
		RegisterClass(&windowClass);

		// Let's create the main window
		auto* const mainWindow = CreateWindow(TEXT("SFML App"), TEXT("SFML Win32"), WS_SYSMENU | WS_VISIBLE, 200, 200,
		                                      600, 800, NULL, NULL, instance, NULL);

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		auto* engine = new Engine::Engine();
		auto* window = new sf::RenderWindow(mainWindow, settings);
		engine->Init(window);

		Utils::Random::SetSeed(static_cast<unsigned int>(time(nullptr)));

		Game::GameMain* gameMain = new Game::GameMain();
		gameMain->Init();

		// Loop until a WM_QUIT message is received
		MSG message;
		message.message = static_cast<UINT>(~WM_QUIT);
		while (message.message != WM_QUIT)
		{
			if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				// If a message was waiting in the message queue, process it
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else
			{
				sf::Event event{};
				while (window->pollEvent(event))
				{
					if (event.type == sf::Event::MouseButtonPressed)
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							gameMain->LMBClicked(window);
						}
					}
				}

				window->clear();

				gameMain->Update();
				gameMain->Render(window);
				engine->Run();

				window->display();
			}
		}

		gameMain->Destroy();
		delete gameMain;

		window->close();
		DestroyWindow(mainWindow); // Destroy the main window (all its child controls will be destroyed)
		UnregisterClass(TEXT("SFML App"), instance); // Don't forget to un-register the window class

		engine->ShutDown();
		delete engine;
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
