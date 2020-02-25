#include "Rigidbody2D.h"
#include "WorldPhysicsController_Extern.h"
#include "Node.h"
#include "Node2D.h"
#include "Rotate2D.h"
#include "Point2D.h"
#include "MathUtils.h"

#include <cassert>

namespace Core::Components::Physics
{
#pragma region Constructor and Destructor

	Rigidbody2D::Rigidbody2D()
	{
		this->_currentVelocity = new Math::Point2D();
		this->_targetVelocity = new Math::Point2D();
		this->_currentAcceleration = new Math::Point2D();
		this->_resultantForce = new Math::Point2D();

		this->_angularVelocity = 0;
	}

	Rigidbody2D::~Rigidbody2D()
	{
		delete this->_currentVelocity;
		delete this->_targetVelocity;
		delete this->_currentAcceleration;
		delete this->_resultantForce;
	}

#pragma endregion

#pragma region Parent Overrides

	void Rigidbody2D::Ready(BaseComponents::Node* i_node)
	{
		const auto node2d = i_node->GetComponent<Transform::Node2D>();
		const auto rotate2d = i_node->GetComponent<Transform::Rotate2D>();

		assert(node2d != nullptr);
		assert(rotate2d != nullptr);

		this->_node2d = node2d;
		this->_rotate2d = rotate2d;
	}

	void Rigidbody2D::PhysicsProcess(float i_fixedDeltaTime)
	{
		ComputerResultantAcceleration();
		ApplyVelocityAndAcceleration(i_fixedDeltaTime);
		ResetBodyForcesData();
	}

#pragma endregion

#pragma region Setters

	void Rigidbody2D::SetMass(const float i_mass)
	{
		this->_mass = i_mass;
	}

	void Rigidbody2D::SetLinearDrag(const float i_linearDrag)
	{
		this->_linearDrag = i_linearDrag;
	}

	void Rigidbody2D::SetAngularDrag(const float i_angularDrag)
	{
		this->_angularDrag = i_angularDrag;
	}

	void Rigidbody2D::SetGravityScale(const float i_gravityScale)
	{
		this->_gravityScale = i_gravityScale;
	}

#pragma endregion

#pragma region Velocity

	void Rigidbody2D::SetVelocity(const float i_x, const float i_y) const
	{
		this->_targetVelocity->set(i_x, i_y);
	}

	void Rigidbody2D::SetVelocity(Math::Point2D& velocity) const
	{
		this->_targetVelocity->set(velocity.X(), velocity.Y());
	}

	void Rigidbody2D::SetAngularVelocity(const float i_angularVelocity)
	{
		this->_angularVelocity = i_angularVelocity;
	}

#pragma endregion

#pragma region Force/Velocity

	void Rigidbody2D::ResetBodyForcesData() const
	{
		this->_resultantForce->set(0, 0);
		this->_currentAcceleration->set(0, 0);
	}

	void Rigidbody2D::ApplyVelocityAndAcceleration(float i_deltaTime)
	{
		// Angular Motion
		if (this->_angularDrag > 1)
		{
			this->_angularVelocity = 0;
		}
		else
		{
			this->_angularVelocity -= (this->_angularDrag * this->_angularVelocity);
		}
		this->_rotate2d->Rotate(this->_angularVelocity * i_deltaTime);

		// Linear Motion
		auto newVelocity = *this->_currentVelocity + *this->_currentAcceleration * i_deltaTime;
		newVelocity = newVelocity * (1 - i_deltaTime * this->_linearDrag);
		this->_currentVelocity->set(newVelocity.X(), newVelocity.Y());

		Math::Point2D* position = _node2d->GetPosition();
		const auto newPosition = *position + *this->_currentVelocity * i_deltaTime;
		position->set(newPosition.X(), newPosition.Y());
	}

	void Rigidbody2D::ComputerResultantAcceleration() const
	{
		const auto velocityAcceleration = *this->_targetVelocity - *this->_currentVelocity;
		const auto accelerationFromForce = *this->_resultantForce / this->_mass;
		const auto gravityAcceleration = *worldPhysicsController->GetGravity() * this->_gravityScale;
		const auto positiveAcceleration = velocityAcceleration + accelerationFromForce + gravityAcceleration;

		this->_currentAcceleration->set(positiveAcceleration.X(), positiveAcceleration.Y());
	}

	void Rigidbody2D::AddForceAtPosition(Math::Point2D& i_force, Math::Point2D& i_position)
	{
		const Math::Point2D p = *this->_node2d->GetPosition() - i_position;
		const float angle = atan2(p.X(), p.Y()) - atan2(i_force.X(), i_force.Y());
		const float t = p.length() * i_force.length() * sin(angle) * Utils::MathUtils::Rad2Deg;

		this->_angularVelocity += t;
	}

	void Rigidbody2D::AddForce(Math::Point2D& i_force) const
	{
		const Math::Point2D newForce = *this->_resultantForce + i_force;
		this->_resultantForce->set(newForce.X(), newForce.Y());
	}

#pragma endregion
}
