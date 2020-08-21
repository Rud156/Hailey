#pragma once
#include "EnemyAttackController.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Core/Components/Physics/Colliders/BaseCollider.h"
#include "../Common/HealthDisplay.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Enemy
{
	class Enemy
	{
	private:
		static const inline float EnemyLowHealthPercent = 0.3f;
		static const inline float MaxHealth = 300;

		Containers::WeakPtr<EnemyAttackController> _enemyAttackController;
		Containers::SmartPtr<Common::HealthDisplay> _healthDisplay;
		float _currentHealth;

		// Utility Functions
		void HandleEnemyCollided(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider> i_collider,
		                         Math::Point2D i_collisionNormal);
		void SetupEnemyHealthDisplay();
		void UpdateEnemyHealth();

	public:
		// Constructor and Destructor
		Enemy();
		~Enemy();

		// LifeCycle Functions
		void Init();
		void Update(float i_deltaTime);
	};
}
