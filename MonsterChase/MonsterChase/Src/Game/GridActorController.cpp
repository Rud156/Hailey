#include "GridActorController.h"

#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Node2D.h"

namespace Game
{
	// Constructor And Destructor

	GridActorController::GridActorController()
	{
		_gridGameObject = new Core::BaseComponents::Node("Grid Actor");
		_gridGameObject->AddComponent<Core::Components::Transform::Node2D>();

		_gridActorName = nullptr;
		_gridActorHealth = 0;
	}

	GridActorController::~GridActorController()
	{
		delete _gridGameObject;
		delete _gridActorName;
	}

	// Constructor And Destructor

	// Name

	void GridActorController::SetActorName(char* name)
	{
		_gridActorName = name;
	}

	char* GridActorController::GetActorName() const
	{
		return _gridActorName;
	}

	void GridActorController::DeleteActorName() const
	{
		delete _gridActorName;
	}

	// Name

	// Health

	void GridActorController::SetActorHealth(const int healthAmount)
	{
		_gridActorHealth = healthAmount;
	}

	void GridActorController::DecrementHealth(const int amount)
	{
		_gridActorHealth -= amount;
	}

	void GridActorController::IncrementHealth(const int amount)
	{
		_gridActorHealth += amount;
	}

	int GridActorController::GetActorHealth() const
	{
		return _gridActorHealth;
	}

	// Health

	// GameObject

	Core::BaseComponents::Node* GridActorController::GetGameObject() const
	{
		return _gridGameObject;
	}

	// GameObject
}
