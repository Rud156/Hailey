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

#pragma region External Functions

	void GameObjectUpdater::AddGameObject(BaseComponents::Node* i_node)
	{
		this->_gameObjects.push_back(i_node);
		i_node->Ready();
	}

	void GameObjectUpdater::RemoveGameObject(BaseComponents::Node* i_node)
	{
		const auto position = std::find(this->_gameObjects.begin(), this->_gameObjects.end(), i_node);
		if (position != this->_gameObjects.end())
		{
			this->_gameObjects.erase(position);
		}
	}

	const std::vector<BaseComponents::Node*>& GameObjectUpdater::GetGameObjectsByRef() const
	{
		return this->_gameObjects;
	}

	std::vector<BaseComponents::Node*> GameObjectUpdater::GetGameObjectsByVal() const
	{
		return this->_gameObjects;
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
