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
			LoopTimer* _loopTimer{};
			GameObjectUpdater* _gameObjectUpdater{};

		public:
			CoreLoop();
			~CoreLoop();

			static inline sf::RenderWindow* Window;

			void Setup(sf::RenderWindow* i_window);
			void Run() const;
		};
	}
}
