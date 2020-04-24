#pragma once
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Core/Components/Transform/Node2D.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Common
{
	class Projectile : public Core::BaseComponents::Component
	{
	private:
		static const float inline ProjectileVelocity = 300; // Probably needs to increase
		static const float inline DestroyLifetime = 3;

		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;
		Containers::SmartPtr<Core::Components::Physics::Rigidbody2D> _projectileRb;

		float _currentLifeTime;
		Math::Point2D* _launchDirection;

	public:
		// Parent Overrides
		Projectile();
		~Projectile() override;
		void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;
		void Process(float deltaTime) override;
		void Exit() override;

		// External Functions
		void LaunchProjectile(Math::Point2D* i_launchDirection);

		// Utility Functions
		void DestroyProjectile();
	};
}
