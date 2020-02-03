#pragma once
#include <vector>
#include "Node.h"

namespace sf
{
	class RenderWindow;
}

namespace Core
{
	namespace Controllers
	{
		class GameObjectUpdater final
		{
		private:
			std::vector<BaseComponents::Node*> _gameObjects;

		public:
			// Constructor and Destructor
			GameObjectUpdater();
			~GameObjectUpdater();

			// External Functions
			void AddGameObject(BaseComponents::Node* node);
			void RemoveGameObject(BaseComponents::Node* node);

			// LifeCycle Functions
			void Process(float deltaTime);
			void Render(sf::RenderWindow* window);
			void Exit();
		};
	}
}
