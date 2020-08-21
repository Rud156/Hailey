#pragma once
#include "PlayerMovement.h"
#include "../../Commands/InputHandler.h"
#include "../Common/HealthDisplay.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Core/Components/Physics/Colliders/BaseCollider.h"
#include "Src/Core/Components/Transform/Node2D.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Player
{
	class Player
	{
	private:
		static const inline size_t MaxPlayerHealth = 100;

		Containers::WeakPtr<Core::BaseComponents::Node> _player;
		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;
		Containers::SmartPtr<Core::Components::Physics::Rigidbody2D> _playerRb;
		Containers::SmartPtr<PlayerMovement> _playerMovement;
		Containers::SmartPtr<Common::HealthDisplay> _healthDisplay;
		Containers::SmartPtr<Commands::InputHandler> _inputHandler;

		Math::Point2D* _playerPosition{};
		float _currentHealth = 0;

		// Utility Functions
		void SetupPlayerHealthDisplay();
		void HandlePlayerCollided(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider> i_collider,
		                          Math::Point2D i_collisionNormal);
		void UpdatePlayerHealth();

	public:
		// Constructor and Destructor
		Player();
		~Player();

		// LifeCycle Functions
		void Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler);
		void Update(float i_deltaTime);
	};
}
