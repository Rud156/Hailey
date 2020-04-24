#pragma once
#include "PlayerMovement.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Core/Components/Physics/Colliders/BaseCollider.h"
#include "../../Commands/InputHandler.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Player
{
	class Player
	{
	private:
		Containers::SmartPtr<Core::BaseComponents::Node> _player;
		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;
		Containers::SmartPtr<Core::Components::Physics::Rigidbody2D> _playerRb;
		Containers::SmartPtr<PlayerMovement> _playerMovement;
		Containers::SmartPtr<Commands::InputHandler> _inputHandler;

		Math::Point2D* _playerPosition{};

		void HandlePlayerCollided(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider> i_collider);

	public:
		// Constructor and Destructor
		Player();
		~Player();

		// LifeCycle Functions
		void Init(Containers::SmartPtr<Commands::InputHandler> i_inputHandler);
		void Update(float i_deltaTime);
	};
}
