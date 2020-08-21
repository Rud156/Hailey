#pragma once
#include "Src/Core/BaseComponents/Component.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Enemy
{
	class SprayShotAttack : public Core::BaseComponents::Component
	{
	private:
		static const inline float TimeBetweenShots = 0.1f;
		static const inline float AngleIncrementAmount = 15;

		float _currentTimer = 0;
		float _currentAngle = 0;

		// Utility Functions
		void Shoot(Math::Point2D& i_offsetPosition, float i_angle);
	public:
		// Attack Functions
		void LaunchAttack();
		void UpdateAttack(Math::Point2D& i_centerPosition, float i_deltaTime);
		void EndAttack();
	};
}
