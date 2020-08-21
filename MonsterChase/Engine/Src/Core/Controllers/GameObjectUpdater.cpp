#include "GameObjectUpdater.h"
#include "GameObjectUpdater_Extern.h"
#include "Physics/WorldCollisionController.h"
#include "Physics/WorldPhysicsController.h"
#include "Rendering/SpriteRenderController.h"
#include "../../Containers/PointerIncludes.cpp"
#include "../../Utils/Debug.h"

Core::Controllers::GameObjectUpdater* gameObjectUpdater = nullptr;

namespace Core::Controllers
{
#pragma region Constructor and Destructor

	GameObjectUpdater::GameObjectUpdater()
	{
		gameObjectUpdater = this;
		_spriteRenderController = new Rendering::SpriteRenderController();
		_worldPhysicsController = new Physics::WorldPhysicsController();
		_worldCollisionController = new Physics::WorldCollisionController();
	}

	GameObjectUpdater::~GameObjectUpdater()
	{
		Exit();
		this->_gameObjects.clear();
		this->_gameObjectsAddedThisFrame.clear();

		delete this->_spriteRenderController;
		delete this->_worldPhysicsController;
		delete this->_worldCollisionController;

		gameObjectUpdater = nullptr;
	}

#pragma endregion

#pragma region GameObject Array Modification

	void GameObjectUpdater::AddGameObject(Containers::SmartPtr<BaseComponents::Node> i_node)
	{
		this->_gameObjectUpdaterLock.lock();

		this->_gameObjectsAddedThisFrame.push_back(i_node);
		i_node->Ready();

		this->_gameObjectUpdaterLock.unlock();
	}

	void GameObjectUpdater::RemoveGameObject(const Containers::SmartPtr<BaseComponents::Node> i_node)
	{
		this->_gameObjectUpdaterLock.lock();

		const Containers::WeakPtr<BaseComponents::Node> weakPtr = Containers::WeakPtr<BaseComponents::Node>(i_node);
		this->_gameObjectsToBeRemoved.push_back(weakPtr);

		this->_gameObjectUpdaterLock.unlock();
	}

	void GameObjectUpdater::RemoveGameObjectImmediate(Containers::SmartPtr<BaseComponents::Node> i_node)
	{
		this->_gameObjectUpdaterLock.lock();

		size_t instanceId = i_node->GetInstanceId();
		const auto position = std::find_if(this->_gameObjectsAddedThisFrame.begin(),
		                                   this->_gameObjectsAddedThisFrame.end(),
		                                   [&instanceId](Containers::SmartPtr<BaseComponents::Node> gameObject)
		                                   {
			                                   return gameObject->GetInstanceId() == instanceId;
		                                   }
		);
		if (position != this->_gameObjectsAddedThisFrame.end())
		{
			(*position)->Exit();
			this->_gameObjectsAddedThisFrame.erase(position);
		}

		this->_gameObjectUpdaterLock.unlock();
	}

#pragma endregion

#pragma region Data Access

	std::vector<Containers::SmartPtr<BaseComponents::Node>> GameObjectUpdater::GetAllGameObjects()
	{
		this->_gameObjectUpdaterLock.lock();

		std::vector<Containers::SmartPtr<BaseComponents::Node>> nodesCopy;
		// nodesCopy.reserve(this->_gameObjects.size());

		for (const auto node : this->_gameObjects)
		{
			Containers::SmartPtr<BaseComponents::Node> smartPtrCopy(node);
			nodesCopy.push_back(smartPtrCopy);
		}

		this->_gameObjectUpdaterLock.unlock();

		return nodesCopy;
	}

	Containers::WeakPtr<BaseComponents::Node> GameObjectUpdater::GetGameObjectByName(std::string_view i_name)
	{
		this->_gameObjectUpdaterLock.lock();
		for (auto node : this->_gameObjects)
		{
			if (node->GetName() == i_name)
			{
				this->_gameObjectUpdaterLock.unlock();

				Containers::WeakPtr<BaseComponents::Node> weakPtrCopy(node);
				return weakPtrCopy;
			}
		}
		this->_gameObjectUpdaterLock.unlock();

		Containers::WeakPtr<BaseComponents::Node> weakPtr;
		return weakPtr;
	}

	Containers::WeakPtr<BaseComponents::Node> GameObjectUpdater::GetGameObjectByTag(std::string_view i_tag)
	{
		this->_gameObjectUpdaterLock.lock();
		for (auto node : this->_gameObjects)
		{
			if (node->GetTag() == i_tag)
			{
				this->_gameObjectUpdaterLock.unlock();

				Containers::WeakPtr<BaseComponents::Node> weakPtrCopy(node);
				return weakPtrCopy;
			}
		}
		this->_gameObjectUpdaterLock.unlock();

		Containers::WeakPtr<BaseComponents::Node> weakPtr;
		return weakPtr;
	}

	std::vector<Containers::WeakPtr<BaseComponents::Node>> GameObjectUpdater::GetAllGameObjectsByTag(
		std::string_view i_tag
	)
	{
		std::vector<Containers::WeakPtr<BaseComponents::Node>> commonGameObjects;

		this->_gameObjectUpdaterLock.lock();
		for (auto node : this->_gameObjects)
		{
			if (node->GetTag() == i_tag)
			{
				Containers::WeakPtr<BaseComponents::Node> weakPtrCopy(node);
				commonGameObjects.push_back(weakPtrCopy);
			}
		}
		this->_gameObjectUpdaterLock.unlock();

		return commonGameObjects;
	}

#pragma endregion

#pragma region LifeCycle Functions

	void GameObjectUpdater::Process(float i_deltaTime)
	{
		for (auto node : this->_gameObjectsToBeRemoved)
		{
			size_t instanceId = node.Lock()->GetInstanceId();
			const auto position = std::find_if(this->_gameObjects.begin(), this->_gameObjects.end(),
			                                   [&instanceId](Containers::SmartPtr<BaseComponents::Node> gameObject)
			                                   {
				                                   return gameObject->GetInstanceId() == instanceId;
			                                   }
			);

			if (position != this->_gameObjects.end())
			{
				(*position)->Exit();
				this->_gameObjects.erase(position);
			}
		}
		this->_gameObjectsToBeRemoved.clear();

		for (auto node : this->_gameObjectsAddedThisFrame)
		{
			auto collider = node->GetComponent<Components::Physics::Colliders::BaseCollider>();
			if (collider)
			{
				this->_worldCollisionController->AddColliderToWorld(collider.Lock());
			}

			this->_gameObjects.push_back(node);
		}
		this->_gameObjectsAddedThisFrame.clear();

		for (auto node : this->_gameObjects)
		{
			node->Process(i_deltaTime);
		}

		this->_worldPhysicsController->RunPhysicsProcess(i_deltaTime);
		this->_worldCollisionController->Process(i_deltaTime);
	}

	void GameObjectUpdater::Render(sf::RenderWindow* i_window)
	{
		for (auto node : this->_gameObjects)
		{
			node->SetupRender();
		}
		this->_spriteRenderController->RenderNodes(i_window);

		Physics::WorldCollisionController::RenderDebug(i_window);
	}


	void GameObjectUpdater::Exit()
	{
		this->_worldCollisionController->Exit();

		for (auto node : this->_gameObjects)
		{
			node->Exit();
		}

		for (auto node : this->_gameObjectsAddedThisFrame)
		{
			node->Exit();
		}
	}

#pragma endregion
}
