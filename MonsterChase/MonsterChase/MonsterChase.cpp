// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Allocators.h"
#include <SFML/Graphics.hpp>

#include "Point2D.h"
#include "Node.h"
#include "Node2D.h"
#include "Rotate2D.h"
#include "Scale2D.h"
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "Debug.h"

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
		const HWND mainWindow = CreateWindow(TEXT("SFML App"), TEXT("SFML Win32"), WS_SYSMENU | WS_VISIBLE, 200, 200,
		                                     800, 640, NULL, NULL, instance, NULL);

		const auto solutionDir = SOLUTION_DIR; // This won't work in release builds as SOLUTION_DIR does not exist then
		std::string goodGuyPath = solutionDir;
		goodGuyPath += "Assets/GoodGuy.png";

		auto engine = new Engine::Engine();
		auto window = new sf::RenderWindow(mainWindow);
		engine->Init(window);

		auto goodGuy = new Core::BaseComponents::Node(); // Good Guy GameObject
		goodGuy->AddComponent<Core::Components::Transform::Rotate2D>();
		goodGuy->AddComponent<Core::Components::Transform::Scale2D>();
		const auto goodGuyPosition = goodGuy->AddComponent<Core::Components::Transform::Node2D>();
		goodGuyPosition->GetPosition()->set(400, 0);
		const auto goodGuySprite = goodGuy->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		goodGuySprite->LoadTexture(goodGuyPath);
		const auto goodGuyRb = goodGuy->AddComponent<Core::Components::Physics::Rigidbody2D>();
		
		const float xVelocity = 100;
		Math::Point2D velocity(xVelocity, 0);

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
					if (event.type == sf::Event::Closed)
					{
						window->close();
					}

					switch (event.type)
					{
					case sf::Event::KeyPressed:
						{
							switch (event.key.code)
							{
							case sf::Keyboard::Left:
								{
									velocity.setX(-xVelocity);
									goodGuyRb->SetLinearDrag(0.05f);
									goodGuyRb->SetVelocity(velocity);
								}
								break;

							case sf::Keyboard::Right:
								{
									velocity.setX(xVelocity);
									goodGuyRb->SetLinearDrag(0.05f);
									goodGuyRb->SetVelocity(velocity);
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
							// TODO: Remove this later on...
							velocity.setX(0);
							goodGuyRb->SetLinearDrag(1);
							goodGuyRb->SetVelocity(velocity);
						}
						break;
					}
				}

				window->clear();
				engine->Run();
				window->display();
			}
		}

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
