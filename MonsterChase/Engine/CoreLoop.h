#pragma once

namespace sf
{
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
			sf::Clock* _clock{};
			GameObjectUpdater* _gameObjectUpdater{};

		public:
			CoreLoop();
			~CoreLoop();

			void Setup();
			void Run() const;
		};
	}
}
