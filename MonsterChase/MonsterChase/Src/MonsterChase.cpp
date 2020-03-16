// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Src/Containers/Tests/PointerTest.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Core/Loaders/JsonGOLoader.h"
#include "Src/Engine.h"
#include "Src/Memory/MemorySystem.h"
#include "Src/Utils/Tests/MathUtilsUnitTest.h"
#include "Src/Utils/Debug.h"
#include "Src/Core/Controllers/GameObjectUpdater_Extern.h"
#include "Src/Core/Controllers/LoopTimer.h"
#include "Src/Utils/Random.h"
#include <SFML/Graphics.hpp>

#include <conio.h>
#include <cassert>
#include <iostream>
#include <string>
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
		const auto mainWindow = CreateWindow(TEXT("SFML App"), TEXT("SFML Win32"), WS_SYSMENU | WS_VISIBLE, 200, 200,
		                                     800, 640, NULL, NULL, instance, NULL);

		const auto assetsDir = Core::Loaders::FileLoader::Assets;

		// TODO: Remove this later on...
		const auto updateTime = 0.3f;
		double currentUpdateTime = 0;

		std::string jsonDataPath = assetsDir;
		jsonDataPath += "/Data/TestData.json";

		std::string goodGuyPath = assetsDir;
		goodGuyPath += "/Images/GoodGuy.png";

		auto engine = new Engine::Engine();
		auto window = new sf::RenderWindow(mainWindow);
		engine->Init(window);

		Utils::Random::SetSeed(static_cast<unsigned int>(time(nullptr)));

		std::string fontPath = assetsDir;
		fontPath += "/Fonts/Oswald-Medium.ttf";
		sf::Font font;
		if (!font.loadFromFile(fontPath))
		{
			Utils::Debug::LogOutputToWindow("Invalid File Path");
			assert(false);
		}

		sf::Text headerText;
		headerText.setFont(font);
		headerText.setString("Press SPACE");
		headerText.setCharacterSize(24);
		headerText.setFillColor(sf::Color::White);
		headerText.setPosition(320, 0);

		sf::Text gameObjectsText;
		gameObjectsText.setFont(font);
		gameObjectsText.setCharacterSize(24);
		gameObjectsText.setFillColor(sf::Color::White);

		sf::Text fpsText;
		fpsText.setFont(font);
		fpsText.setCharacterSize(24);
		fpsText.setFillColor(sf::Color::White);
		fpsText.setPosition(0, 100);

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
					switch (event.type)
					{
					case sf::Event::KeyPressed:
						{
							switch (event.key.code)
							{
							case sf::Keyboard::Space:
								{
									for (int i = 0; i < 10; i++)
									{
										Core::Loaders::JsonGOLoader::LoadJsonGameObjectAsync(jsonDataPath.c_str());
									}
								}
								break;

							default:
								// Don't do anything here...
								break;
							}
						}
						break;

					default:
						{
						}
						break;
					}
				}

				window->clear();
				engine->Run();

				// TODO: Remove this later on...
				currentUpdateTime -= Core::Controllers::LoopTimer::DeltaTime;
				if (currentUpdateTime <= 0)
				{
					// TODO: Remove this later on...
					size_t totalObjectsCount = gameObjectUpdater->GetAllGameObjects().size();
					std::string data = "Total Objects: ";
					data += std::to_string(totalObjectsCount);
					gameObjectsText.setString(data);

					// TODO: Remove this later on...
					double fps = 1.0 / Core::Controllers::LoopTimer::DeltaTime;
					std::string fpsData = "FPS: ";
					fpsData += std::to_string(fps);
					fpsText.setString(fpsData);

					currentUpdateTime = updateTime;
				}

				window->draw(gameObjectsText);
				window->draw(headerText);
				window->draw(fpsText);

				window->display();
			}
		}

		// Unit Tests
		Utils::Tests::MathUtilsUnitTest::RunTest();
		Containers::Tests::PointerTest::RunPointerUnitTest();

		window->close();
		DestroyWindow(mainWindow); // Destroy the main window (all its child controls will be destroyed)
		UnregisterClass(TEXT("SFML App"), instance); // Don't forget to unregister the window class

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
