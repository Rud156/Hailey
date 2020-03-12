#include "WorldPhysicsController.h"
#include "WorldPhysicsController_Extern.h"
#include "../../../Maths/Point2D.h"
#include "../../BaseComponents/Node.h"
#include "../GameObjectUpdater_Extern.h"

Core::Controllers::Physics::WorldPhysicsController* worldPhysicsController = nullptr;

namespace Core::Controllers::Physics
{
#pragma region Constructor/Destructor

	WorldPhysicsController::WorldPhysicsController()
	{
		this->_globalGravity = new Math::Point2D(0, 9.8f);
		this->_accumulator = 0;

		worldPhysicsController = this;
	}

	WorldPhysicsController::~WorldPhysicsController()
	{
		delete this->_globalGravity;
		worldPhysicsController = nullptr;
	}

#pragma endregion

#pragma region Gravity

	void WorldPhysicsController::SetGravity(const float i_x, const float i_y) const
	{
		this->_globalGravity->set(i_x, i_y);
	}

	Math::Point2D* WorldPhysicsController::GetGravity() const
	{
		return this->_globalGravity;
	}

#pragma endregion

#pragma region Fixed Timestep

	void WorldPhysicsController::RunPhysicsProcess(float i_deltaTime)
	{
		this->_accumulator += i_deltaTime;

		while (this->_accumulator >= WorldPhysicsController::DefaultSimulationTime)
		{
			for (auto node : gameObjectUpdater->GetGameObjectsByRef())
			{
				node->PhysicsProcess(WorldPhysicsController::DefaultSimulationTime);
			}
			this->_accumulator -= WorldPhysicsController::DefaultSimulationTime;
		}
	}

#pragma endregion
}
