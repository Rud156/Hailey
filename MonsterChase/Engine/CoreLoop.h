#pragma once

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace Controllers
	{
		class GameObjectUpdater;
		class LoopTimer;
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
			LoopTimer* _loopTimer{};
			GameObjectUpdater* _gameObjectUpdater{};

		public:
			CoreLoop();
			~CoreLoop();

			void Setup(sf::RenderWindow* i_window);
			void Run() const;
		};
	}
}
