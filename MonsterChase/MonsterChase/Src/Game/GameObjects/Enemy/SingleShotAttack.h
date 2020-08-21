#pragma once
#include "Src/Core/BaseComponents/Component.h"

#include <vector>

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Enemy
{
	class SingleShotAttack : public Core::BaseComponents::Component
	{
	private:

		static const inline float TimeBetweenShots = 0.5f;
		float _currentTimer = 0;
		size_t _currentIndex = 0;

		// Utility Functions
		void Shoot(Math::Point2D& i_offsetPosition);

	public:
		// Attack Functions
		void LaunchAttack();
		void UpdateAttack(std::vector<Math::Point2D> i_innerShootingOffsets,
		                  std::vector<Math::Point2D> i_outerShootingOffsets,
		                  float i_deltaTime);
		void EndAttack();
	};
}
