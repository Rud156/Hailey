#pragma once

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
			sf::RenderWindow* _window{};
			sf::Clock* _clock{};
			GameObjectUpdater* _gameObjectUpdater{};

		public:
			CoreLoop();
			~CoreLoop();

			void Setup(sf::RenderWindow* window);
			void Run() const;
		};
	}
}
