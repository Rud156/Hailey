#pragma once
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Containers/SmartPtr.h"

namespace Game::GameObjects::Player
{
	class PlayerMovement final : public Core::BaseComponents::Component
	{
	private:
		enum class HorizontalDirection
		{
			Left,
			Right,
			NoDirection
		};

		enum class VerticalDirection
		{
			Forward,
			Backward,
			NoDirection
		};

		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;
		Containers::SmartPtr<Core::Components::Transform::Rotate2D> _rotate2d;
		Containers::SmartPtr<Core::Components::Physics::Rigidbody2D> _rb;

		// Horizontal Movement
		float _hCurrentMovementVelocity = 0;
		static const inline float HMovementChangeRate = 600;
		static const inline float HMaxVelocityAmount = 300;
		HorizontalDirection _hDirection = HorizontalDirection::NoDirection;

		// Vertical Movement 
		float _vCurrentMovementVelocity = 0;
		static const inline float VMovementChangeRate = 500;
		static const inline float VMaxVelocityAmount = 250;
		VerticalDirection _vDirection = VerticalDirection::NoDirection;

		// Rotations
		static const inline float MaxRotationAmount = 7;
		static const inline float RotationLerpSpeed = 7;
		float _targetRotation = 0;
		float _startRotation = 0;
		float _rotationLerpAmount = 0;

		// Size
		float _width = 0;
		float _height = 0;

		// Horizontal Movement
		void UpdateHorizontalMovement(float i_deltaTime);
		void SetHorizontalDirection(HorizontalDirection i_direction);

		// Vertical Movement
		void UpdateVerticalMovement(float i_deltaTime);
		void SetVerticalDirection(VerticalDirection i_direction);

		// Rotations
		void UpdateRotations(float i_deltaTime);

		// Utility Functions
		void ResetDirections();

	public:
		// Overridden Parent
		~PlayerMovement() override;
		void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;
		void Process(float i_deltaTime) override;
		void Exit() override;

		// Movement Functions
		void MoveLeft();
		void MoveRight();
		void MoveForward();
		void MoveBackward();

		// Utility Functions
		void SetSpriteInfo(float i_width, float i_height);
	};
}
