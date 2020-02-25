#pragma once
#include <vector>
#include "Node.h"

namespace Core::Controllers
{
	namespace Rendering
	{
		class SpriteRenderController;
	}

	namespace Physics
	{
		class WorldPhysicsController;
	}
}

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
			Rendering::SpriteRenderController* _spriteRenderController;
			Physics::WorldPhysicsController* _worldPhysicsController;

		public:
			// Constructor and Destructor
			GameObjectUpdater();
			~GameObjectUpdater();

			// External Functions
			void AddGameObject(BaseComponents::Node* i_node);
			void RemoveGameObject(BaseComponents::Node* i_node);

			// LifeCycle Functions
			void Process(float i_deltaTime);
			void Render(sf::RenderWindow* i_window);
			void Exit();
		};
	}
}
