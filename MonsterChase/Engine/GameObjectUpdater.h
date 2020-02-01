#pragma once
#include <vector>
#include "Node.h"

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
			void Exit();
		};
	}
}
