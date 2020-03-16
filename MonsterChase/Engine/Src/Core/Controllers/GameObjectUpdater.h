#pragma once
#include <mutex>
#include <string_view>
#include <vector>

namespace Core::BaseComponents
{
	class Node;
}

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

			std::mutex _gameObjectUpdaterLock;

		public:
			// Constructor and Destructor
			GameObjectUpdater();
			~GameObjectUpdater();

			// GameObject Array Modification
			void AddGameObject(BaseComponents::Node* i_node);
			void RemoveGameObject(BaseComponents::Node* i_node);

			// Data Access
			[[nodiscard]] std::vector<BaseComponents::Node*> GetAllGameObjects();
			[[nodiscard]] BaseComponents::Node* GetGameObjectByName(std::string_view i_name);
			[[nodiscard]] BaseComponents::Node* GetGameObjectByTag(std::string_view i_tag);
			[[nodiscard]] std::vector<BaseComponents::Node*> GetAllGameObjectsByTag(std::string_view i_tag);

			// LifeCycle Functions
			void Process(float i_deltaTime);
			void Render(sf::RenderWindow* i_window);
			void Exit();
		};
	}
}
