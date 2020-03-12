#pragma once

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
		float _accumulator;

	public:
		// Constructor/Destructor
		WorldPhysicsController();
		~WorldPhysicsController();

		// Gravity
		void SetGravity(float i_x, float i_y) const;
		[[nodiscard]] Math::Point2D* GetGravity() const;

		// TimeStep
		void RunPhysicsProcess(float i_deltaTime);
	};
}
