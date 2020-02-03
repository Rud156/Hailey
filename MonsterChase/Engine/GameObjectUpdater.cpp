#include "GameObjectUpdater.h"
#include "GameObjectUpdater_Extern.h"

Core::Controllers::GameObjectUpdater* gameObjectUpdater = nullptr;

namespace Core
{
	namespace Controllers
	{
#pragma region Constructor and Destructor

		GameObjectUpdater::GameObjectUpdater()
		{
			gameObjectUpdater = this;
		}

		GameObjectUpdater::~GameObjectUpdater()
		{
			Exit();
			this->_gameObjects.clear();
			gameObjectUpdater = nullptr;
		}

#pragma endregion

#pragma region External Functions

		void GameObjectUpdater::AddGameObject(BaseComponents::Node* node)
		{
			this->_gameObjects.push_back(node);
			node->Ready();
		}

		void GameObjectUpdater::RemoveGameObject(BaseComponents::Node* node)
		{
			const auto position = std::find(this->_gameObjects.begin(), this->_gameObjects.end(), node);
			if (position != this->_gameObjects.end())
			{
				this->_gameObjects.erase(position);
			}
		}

#pragma endregion

#pragma region LifeCycle Functions

		void GameObjectUpdater::Process(float deltaTime)
		{
			for (auto node : this->_gameObjects)
			{
				node->Process(deltaTime);
			}
		}

		void GameObjectUpdater::Render(sf::RenderWindow* window)
		{
			for (auto node : this->_gameObjects)
			{
				node->Render(window);
			}
		}


		void GameObjectUpdater::Exit()
		{
			for (auto node : this->_gameObjects)
			{
				node->Exit();
			}
		}

#pragma endregion
	}
}
