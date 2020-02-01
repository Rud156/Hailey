// MonsterChase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Allocators.h"

#include <conio.h>
#include <cassert>
#include <iostream>

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
		sf::RenderWindow* window = engine->Init(800, 640, "SFML Renderer!!!");

		sf::Texture goodGuyTexture;
		sf::Texture badGuyTexture;

		if (!goodGuyTexture.loadFromFile(goodGuyPath))
		{
			std::cout << "Invalid File Path. Unable to load texture" << std::endl;
		}
		if (!badGuyTexture.loadFromFile(badGuyPath))
		{
			std::cout << "Invalid File Path. Unable to load texture" << std::endl;
		}

		sf::Sprite goodGuySprite;
		goodGuySprite.setTexture(goodGuyTexture);
		goodGuySprite.setPosition(400, 320);
		sf::Sprite badGuySprite;
		badGuySprite.setTexture(badGuyTexture);
		badGuySprite.setPosition(10, 100);

		while (window->isOpen())
		{
			sf::Event event{};
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
				}
			}

			window->clear();

			engine->Run();
			window->draw(goodGuySprite);
			window->draw(badGuySprite);

			window->display();
		}

		engine->ShutDown();
		delete window;
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
