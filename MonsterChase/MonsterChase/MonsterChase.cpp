// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Allocators.h"
#include <SFML/Graphics.hpp>

#include "Node.h"
#include "Node3D.h"
#include "SpriteRenderer.h"

#include <conio.h>
#include <cassert>
#include <iostream>
#include <string>

// Super Hacky But Works
class RunBeforeMain
{
public:
	RunBeforeMain() = default;

	~RunBeforeMain()
	{
		Memory::MemorySystem::destroy();
	}
};

RunBeforeMain runBeforeMain;

int main()
{
	// SFML Sprites. Origin Point is Top Right Corner. Don't keep this here...
	{
		const auto solutionDir = SOLUTION_DIR;
		// This won't work in release builds as SOLUTION_DIR does not exist then
		std::string goodGuyPath = solutionDir;
		goodGuyPath += "Assets/GoodGuy.png";
		std::string badGuyPath = solutionDir;
		badGuyPath += "Assets/BadGuy.png";

		auto engine = new Engine::Engine();
		auto window = new sf::RenderWindow(sf::VideoMode(800, 640), "SFML Renderer!!!");
		engine->Init(window);

		auto goodGuy = new Core::BaseComponents::Node(); // Good Guy GameObject
		auto badGuy = new Core::BaseComponents::Node(); // Bad Guy GameObject
		const auto goodGuyPosition = goodGuy->AddComponent<Core::Components::Transform::Node3D>();
		goodGuyPosition->GetPosition()->set(400, 320, 0);
		const auto badGuyPosition = badGuy->AddComponent<Core::Components::Transform::Node3D>();
		badGuyPosition->GetPosition()->set(10, 100, 0);
		const auto goodGuySprite = goodGuy->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		goodGuySprite->LoadTexture(goodGuyPath);
		const auto badGuySprite = badGuy->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		badGuySprite->LoadTexture(badGuyPath);

		while (window->isOpen())
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
				case sf::Event::Closed:
					window->close();
					break;

				case sf::Event::KeyPressed:
					{
						switch (event.key.code)
						{
						case sf::Keyboard::A:
							{
								const auto position = goodGuyPosition->GetPosition();
								position->setX(position->X() - 1);
							}
							break;

						case sf::Keyboard::D:
							{
								const auto position = goodGuyPosition->GetPosition();
								position->setX(position->X() + 1);
							}
							break;

						case sf::Keyboard::Left:
							{
								const auto position = badGuyPosition->GetPosition();
								position->setX(position->X() - 1);
							}
							break;

						case sf::Keyboard::Right:
							{
								const auto position = badGuyPosition->GetPosition();
								position->setX(position->X() + 1);
							}
							break;

						default:
							// Do nothing here...
							break;
						}
					}
					break;

				default:
					// Do nothing here...
					break;
				}
			}

			window->clear();
			engine->Run();
			window->display();
		}

		engine->ShutDown();
		delete goodGuy;
		delete badGuy;
		delete engine;
	}


#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	(void)_getch();
	return 0;
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
