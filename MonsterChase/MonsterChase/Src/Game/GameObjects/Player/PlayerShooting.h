#pragma once
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Physics/Colliders/BaseCollider.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Player
{
	class PlayerShooting final : public Core::BaseComponents::Component
	{
	private:
		static const inline float ShootDelay = 0.15f;
		float _shootingTimer;

		Math::Point2D* _launchOffset;

		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;
		Containers::SmartPtr<Core::Components::Transform::Rotate2D> _rotate2d;

	public:
		// Constructor
		PlayerShooting();

		// Shooting Functions
		void Shoot();

		// Parent Overrides
		~PlayerShooting() override;
		void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;
		void Process(float i_deltaTime) override;
	};
}
