#pragma once
#include <string>

namespace sf
{
	class RenderWindow;
	class Clock;
}

namespace Core
{
	namespace Controllers
	{
		class GameObjectUpdater;
	}
}

namespace Core
{
	namespace Controllers
	{
		class CoreLoop
		{
		private:
			sf::RenderWindow* _windowContext{};
			sf::Clock* _clock{};

			GameObjectUpdater* _gameObjectUpdater{};

		public:
			CoreLoop();
			~CoreLoop();

			sf::RenderWindow* Setup(int windowWidth, int windowHeight, const std::string& windowTitle);
			void Run() const;
		};
	}
}
