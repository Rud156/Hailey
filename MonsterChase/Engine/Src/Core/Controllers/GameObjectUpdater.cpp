#include "GameObjectUpdater.h"
#include "GameObjectUpdater_Extern.h"
#include "../BaseComponents/Node.h"
#include "Physics/WorldPhysicsController.h"
#include "Rendering/SpriteRenderController.h"

Core::Controllers::GameObjectUpdater* gameObjectUpdater = nullptr;

namespace Core::Controllers
{
#pragma region Constructor and Destructor

	GameObjectUpdater::GameObjectUpdater()
	{
		gameObjectUpdater = this;
		_spriteRenderController = new Rendering::SpriteRenderController();
		_worldPhysicsController = new Physics::WorldPhysicsController();
	}

	GameObjectUpdater::~GameObjectUpdater()
	{
		Exit();

		for (auto gameObject : _gameObjects)
		{
			delete gameObject;
		}

		this->_gameObjects.clear();

		delete this->_spriteRenderController;
		delete this->_worldPhysicsController;

		gameObjectUpdater = nullptr;
	}

#pragma endregion

#pragma region GameObject Array Modification

	void GameObjectUpdater::AddGameObject(BaseComponents::Node* i_node)
	{
		this->_gameObjectUpdaterLock.lock();

		this->_gameObjects.push_back(i_node);
		i_node->Ready();

		this->_gameObjectUpdaterLock.unlock();
	}

	void GameObjectUpdater::RemoveGameObject(BaseComponents::Node* i_node)
	{
		this->_gameObjectUpdaterLock.lock();

		const auto position = std::find(this->_gameObjects.begin(), this->_gameObjects.end(), i_node);
		if (position != this->_gameObjects.end())
		{
			this->_gameObjects.erase(position);
		}

		this->_gameObjectUpdaterLock.unlock();
	}

#pragma endregion

#pragma region Data Access

	std::vector<BaseComponents::Node*> GameObjectUpdater::GetAllGameObjects()
	{
		this->_gameObjectUpdaterLock.lock();
		std::vector<BaseComponents::Node*> nodesCopy(this->_gameObjects);
		this->_gameObjectUpdaterLock.unlock();

		return nodesCopy;
	}

	BaseComponents::Node* GameObjectUpdater::GetGameObjectByName(std::string_view i_name)
	{
		for (auto node : this->_gameObjects)
		{
			if (node->GetName() == i_name)
			{
				return node;
			}
		}

		return nullptr;
	}

	BaseComponents::Node* GameObjectUpdater::GetGameObjectByTag(std::string_view i_tag)
	{
		for (auto node : this->_gameObjects)
		{
			if (node->GetTag() == i_tag)
			{
				return node;
			}
		}

		return nullptr;
	}

	std::vector<BaseComponents::Node*> GameObjectUpdater::GetAllGameObjectsByTag(std::string_view i_tag)
	{
		std::vector<BaseComponents::Node*> commonGameObjects;

		for (auto node : this->_gameObjects)
		{
			if (node->GetTag() == i_tag)
			{
				commonGameObjects.push_back(node);
			}
		}

		return commonGameObjects;
	}

#pragma endregion

#pragma region LifeCycle Functions

	void GameObjectUpdater::Process(float i_deltaTime)
	{
		for (auto node : this->_gameObjects)
		{
			node->Process(i_deltaTime);
		}
		this->_worldPhysicsController->RunPhysicsProcess(i_deltaTime);
	}

	void GameObjectUpdater::Render(sf::RenderWindow* i_window)
	{
		for (auto node : this->_gameObjects)
		{
			node->SetupRender();
		}
		this->_spriteRenderController->RenderNodes(i_window);
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
