#include "WorldPhysicsController.h"
#include "WorldPhysicsController_Extern.h"
#include "Node.h"
#include "Point2D.h"

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

	void WorldPhysicsController::AddNode(BaseComponents::Node* i_node)
	{
		this->_nodes.push_back(i_node);
	}

	void WorldPhysicsController::RemoveNode(BaseComponents::Node* i_node)
	{
		const auto position = std::find(this->_nodes.begin(), this->_nodes.end(), i_node);
		if (position != this->_nodes.end())
		{
			this->_nodes.erase(position);
		}
	}

	void WorldPhysicsController::RunPhysicsProcess(float i_deltaTime)
	{
		this->_accumulator += i_deltaTime;

		while (this->_accumulator >= WorldPhysicsController::DefaultSimulationTime)
		{
			for (auto node : this->_nodes)
			{
				node->PhysicsProcess(WorldPhysicsController::DefaultSimulationTime);
			}
			this->_accumulator -= WorldPhysicsController::DefaultSimulationTime;
		}
	}

#pragma endregion
}
