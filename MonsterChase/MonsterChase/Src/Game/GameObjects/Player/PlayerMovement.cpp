#include "PlayerMovement.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Utils/MathUtils.h"
#include "Src/Maths/Point2D.h"
#include "Src/Core/Controllers/CoreLoop.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <cmath>

namespace Game::GameObjects::Player
{
#pragma region Overridden Parent

	PlayerMovement::~PlayerMovement() = default;

	void PlayerMovement::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		Containers::WeakPtr<Core::Components::Transform::Node2D> node2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		Containers::WeakPtr<Core::Components::Transform::Rotate2D> rotate2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Rotate2D>();
		Containers::WeakPtr<Core::Components::Physics::Rigidbody2D> rb =
			i_node.Lock()->GetComponent<Core::Components::Physics::Rigidbody2D>();

		assert(node2d);
		assert(rotate2d);
		assert(rb);

		this->_node2d = node2d.Lock();
		this->_rotate2d = rotate2d.Lock();
		this->_rb = rb.Lock();

		SetHorizontalDirection(HorizontalDirection::NoDirection);
		SetVerticalDirection(VerticalDirection::NoDirection);
	}

	void PlayerMovement::Process(const float i_deltaTime)
	{
		UpdateHorizontalMovement(i_deltaTime);
		UpdateVerticalMovement(i_deltaTime);
		UpdateRotations(i_deltaTime);

		ResetDirections();
	}

	void PlayerMovement::Exit()
	{
		SetHorizontalDirection(HorizontalDirection::NoDirection);
		SetVerticalDirection(VerticalDirection::NoDirection);
	}

#pragma endregion

#pragma region Movement Functions

	void PlayerMovement::MoveLeft()
	{
		SetHorizontalDirection(HorizontalDirection::Left);
	}

	void PlayerMovement::MoveRight()
	{
		SetHorizontalDirection(HorizontalDirection::Right);
	}

	void PlayerMovement::MoveForward()
	{
		SetVerticalDirection(VerticalDirection::Forward);
	}

	void PlayerMovement::MoveBackward()
	{
		SetVerticalDirection(VerticalDirection::Backward);
	}

#pragma endregion

#pragma region Horizontal Movement

	void PlayerMovement::UpdateHorizontalMovement(const float i_deltaTime)
	{
		if (this->_hDirection == HorizontalDirection::Left)
		{
			this->_hCurrentMovementVelocity -= PlayerMovement::HMovementChangeRate * i_deltaTime;
			if (std::abs(this->_hCurrentMovementVelocity) > PlayerMovement::HMaxVelocityAmount)
			{
				this->_hCurrentMovementVelocity = -PlayerMovement::HMaxVelocityAmount;
			}
		}
		else if (this->_hDirection == HorizontalDirection::Right)
		{
			this->_hCurrentMovementVelocity += PlayerMovement::HMovementChangeRate * i_deltaTime;
			if (std::abs(this->_hCurrentMovementVelocity) > PlayerMovement::HMaxVelocityAmount)
			{
				this->_hCurrentMovementVelocity = PlayerMovement::HMaxVelocityAmount;
			}
		}
		else
		{
			// This means the object is moving left
			if (_hCurrentMovementVelocity < 0)
			{
				this->_hCurrentMovementVelocity += PlayerMovement::HMovementChangeRate * i_deltaTime;
				if (this->_hCurrentMovementVelocity > 0)
				{
					this->_hCurrentMovementVelocity = 0;
				}
			}
				// This means that the object is moving right
			else
			{
				this->_hCurrentMovementVelocity -= PlayerMovement::HMovementChangeRate * i_deltaTime;
				if (this->_hCurrentMovementVelocity < 0)
				{
					this->_hCurrentMovementVelocity = 0;
				}
			}
		}

		const float xPosition = this->_node2d->GetPosition()->X();
		if (xPosition < this->_width / 2.0f)
		{
			this->_node2d->GetPosition()->setX(this->_width / 2.0f + 1);
			this->_hCurrentMovementVelocity = 0;
		}
		else if (xPosition > Core::Controllers::CoreLoop::Window->getSize().x - this->_width / 2.0f)
		{
			this->_node2d->GetPosition()->setX(
				Core::Controllers::CoreLoop::Window->getSize().x - this->_width / 2.0f - 1
			);
			this->_hCurrentMovementVelocity = 0;
		}

		this->_rb->SetVelocity(this->_hCurrentMovementVelocity, this->_vCurrentMovementVelocity);
	}

	void PlayerMovement::SetHorizontalDirection(const HorizontalDirection i_direction)
	{
		_hDirection = i_direction;
	}

#pragma endregion

#pragma region Vertical Movement

	void PlayerMovement::UpdateVerticalMovement(const float i_deltaTime)
	{
		if (this->_vDirection == VerticalDirection::Forward)
		{
			this->_vCurrentMovementVelocity -= PlayerMovement::VMovementChangeRate * i_deltaTime;
			if (std::abs(this->_vCurrentMovementVelocity) > PlayerMovement::VMaxVelocityAmount)
			{
				this->_vCurrentMovementVelocity = -PlayerMovement::VMaxVelocityAmount;
			}
		}
		else if (this->_vDirection == VerticalDirection::Backward)
		{
			this->_vCurrentMovementVelocity += PlayerMovement::VMovementChangeRate * i_deltaTime;
			if (std::abs(this->_vCurrentMovementVelocity) > PlayerMovement::VMaxVelocityAmount)
			{
				this->_vCurrentMovementVelocity = PlayerMovement::VMaxVelocityAmount;
			}
		}
		else
		{
			// This means that the object is moving forward
			if (this->_vCurrentMovementVelocity < 0)
			{
				this->_vCurrentMovementVelocity += PlayerMovement::VMovementChangeRate * i_deltaTime;
				if (this->_vCurrentMovementVelocity > 0)
				{
					this->_vCurrentMovementVelocity = 0;
				}
			}
				// This means the object is moving backward
			else
			{
				this->_vCurrentMovementVelocity -= PlayerMovement::VMovementChangeRate * i_deltaTime;
				if (this->_vCurrentMovementVelocity < 0)
				{
					this->_vCurrentMovementVelocity = 0;
				}
			}
		}

		const float yPosition = this->_node2d->GetPosition()->Y();
		if (yPosition < this->_height / 2.0f)
		{
			this->_node2d->GetPosition()->setY(this->_height / 2.0f + 1);
			this->_vCurrentMovementVelocity = 0;
		}
		else if (yPosition > Core::Controllers::CoreLoop::Window->getSize().y - this->_height / 2.0f)
		{
			this->_node2d->GetPosition()->setY(
				Core::Controllers::CoreLoop::Window->getSize().y - this->_height / 2.0f - 1
			);
			this->_vCurrentMovementVelocity = 0;
		}

		this->_rb->SetVelocity(this->_hCurrentMovementVelocity, this->_vCurrentMovementVelocity);
	}

	void PlayerMovement::SetVerticalDirection(const VerticalDirection i_direction)
	{
		_vDirection = i_direction;
	}

#pragma endregion

#pragma region Rotations

	void PlayerMovement::UpdateRotations(const float i_deltaTime)
	{
		const float mappedRotation = Utils::MathUtils::Map(
			-PlayerMovement::HMaxVelocityAmount, PlayerMovement::HMaxVelocityAmount,
			-PlayerMovement::MaxRotationAmount, PlayerMovement::MaxRotationAmount,
			this->_hCurrentMovementVelocity
		);

		if (!Utils::MathUtils::IsEqual(mappedRotation, this->_targetRotation, 0.1f))
		{
			this->_targetRotation = mappedRotation;
			this->_startRotation = this->_rotate2d->GetAngle();
			this->_rotationLerpAmount = 0;
		}

		if (this->_rotationLerpAmount > 1)
		{
			this->_rotationLerpAmount = 1;
		}

		this->_rotate2d->SetAngle(
			Utils::MathUtils::LerpAngleDeg(this->_startRotation, this->_targetRotation, this->_rotationLerpAmount)
		);
		this->_rotationLerpAmount += PlayerMovement::RotationLerpSpeed * i_deltaTime;
	}

#pragma endregion

#pragma region Utility Functions

	void PlayerMovement::ResetDirections()
	{
		SetHorizontalDirection(HorizontalDirection::NoDirection);
		SetVerticalDirection(VerticalDirection::NoDirection);
	}

	void PlayerMovement::SetSpriteSize(const float i_width, const float i_height)
	{
		this->_width = i_width;
		this->_height = i_height;
	}

#pragma endregion
}
