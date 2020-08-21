#pragma once
#include "Src/Core/BaseComponents/Component.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Enemy
{
	class DualShotAttack : public Core::BaseComponents::Component
	{
	private:
		static const inline float TimeBetweenShots = 0.5f;
		float _currentTimer = 0;
		bool _isOuterShot = false;

		// Utility Functions
		void Shoot(Math::Point2D& i_offsetPosition);

	public:
		// Attack Functions
		void LaunchAttack();
		void UpdateAttack(const std::vector<Math::Point2D>& i_innerShootingOffsets,
		                  const std::vector<Math::Point2D>& i_outerShootingOffsets,
		                  float i_deltaTime);
		void EndAttack();
	};
}
