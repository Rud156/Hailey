#pragma once
#include <vector>

namespace Math
{
	class Point2D;
}

namespace Core::BaseComponents
{
	class Node;
}

namespace Core::Controllers::Physics
{
	class WorldPhysicsController
	{
	private:
		const float DefaultSimulationTime = 0.01667f;

		Math::Point2D* _globalGravity;
		std::vector<BaseComponents::Node*> _nodes;
		float _accumulator;

	public:
		// Constructor/Destructor
		WorldPhysicsController();
		~WorldPhysicsController();

		// Gravity
		void SetGravity(float i_x, float i_y) const;
		[[nodiscard]] Math::Point2D* GetGravity() const;

		// TimeStep
		void AddNode(BaseComponents::Node* i_node);
		void RemoveNode(BaseComponents::Node* i_node);
		void RunPhysicsProcess(float i_deltaTime);
	};
}
