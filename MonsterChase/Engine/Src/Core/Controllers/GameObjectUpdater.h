#pragma once
#include "../../Containers/SmartPtr.h"
#include "../../Containers/WeakPtr.h"
#include "../BaseComponents/Node.h"

#include <mutex>
#include <string_view>
#include <vector>

namespace Core::Controllers
{
	namespace Rendering
	{
		class SpriteRenderController;
	}

	namespace Physics
	{
		class WorldPhysicsController;
		class WorldCollisionController;
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
			std::vector<Containers::SmartPtr<BaseComponents::Node>> _gameObjects;
			Rendering::SpriteRenderController* _spriteRenderController;
			Physics::WorldPhysicsController* _worldPhysicsController;
			Physics::WorldCollisionController* _worldCollisionController;

			std::mutex _gameObjectUpdaterLock;

		public:
			// Constructor and Destructor
			GameObjectUpdater();
			~GameObjectUpdater();

			// GameObject Array Modification
			void AddGameObject(Containers::SmartPtr<BaseComponents::Node> i_node);
			void RemoveGameObject(Containers::SmartPtr<BaseComponents::Node> i_node);

			// Data Access
			[[nodiscard]] std::vector<Containers::SmartPtr<BaseComponents::Node>> GetAllGameObjects();
			[[nodiscard]] Containers::WeakPtr<BaseComponents::Node> GetGameObjectByName(std::string_view i_name);
			[[nodiscard]] Containers::WeakPtr<BaseComponents::Node> GetGameObjectByTag(std::string_view i_tag);
			[[nodiscard]] std::vector<Containers::WeakPtr<BaseComponents::Node>> GetAllGameObjectsByTag(
				std::string_view i_tag
			);

			// LifeCycle Functions
			void Process(float i_deltaTime);
			void Render(sf::RenderWindow* i_window);
			void Exit();
		};
	}
}
