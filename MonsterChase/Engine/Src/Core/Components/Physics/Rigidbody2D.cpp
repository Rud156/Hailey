#include "Rigidbody2D.h"
#include "../../../Maths/Point2D.h"
#include "../../../Utils/MathUtils.h"
#include "../../BaseComponents/Node.h"
#include "../../Controllers/Physics/WorldPhysicsController_Extern.h"
#include "../../../Containers/PointerIncludes.cpp"

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

		this->_currentAngularVelocity = 0;
		this->_targetAngularVelocity = 0;
		this->_currentAngularAcceleration = 0;
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

	void Rigidbody2D::Ready(Containers::WeakPtr<BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		Containers::SmartPtr<BaseComponents::Node> gameObject = i_node.Lock();
		auto node2d = gameObject->GetComponent<Transform::Node2D>();
		auto rotate2d = gameObject->GetComponent<Transform::Rotate2D>();

		assert(node2d);
		assert(rotate2d);

		this->_node2d = node2d.Lock();
		this->_rotate2d = rotate2d.Lock();
	}

	void Rigidbody2D::PhysicsProcess(float i_fixedDeltaTime)
	{
		ComputerResultantLinearAcceleration(i_fixedDeltaTime);
		ApplyLinearVelocityAndAcceleration(i_fixedDeltaTime);

		ComputeResultantAngularAcceleration(i_fixedDeltaTime);
		ApplyAngularVelocityAndAcceleration(i_fixedDeltaTime);

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

	Math::Point2D* Rigidbody2D::GetVelocity() const
	{
		return this->_currentVelocity;
	}

	void Rigidbody2D::SetAngularVelocity(const float i_angularVelocity)
	{
		this->_targetAngularVelocity = i_angularVelocity;
	}

	float Rigidbody2D::GetAngularVelocity() const
	{
		return this->_currentAngularVelocity;
	}

#pragma endregion

#pragma region Force/Velocity

	void Rigidbody2D::ResetBodyForcesData()
	{
		this->_resultantForce->set(0, 0);
		this->_currentAcceleration->set(0, 0);
		this->_currentAngularAcceleration = 0;
	}

	void Rigidbody2D::ApplyLinearVelocityAndAcceleration(float i_deltaTime)
	{
		// Linear Motion
		auto newVelocity = *this->_currentVelocity + *this->_currentAcceleration * i_deltaTime;
		newVelocity = newVelocity * (1 - i_deltaTime * this->_linearDrag);
		this->_currentVelocity->set(newVelocity.X(), newVelocity.Y());

		// Apply Position
		Math::Point2D* position = this->_node2d->GetPosition();
		const auto newPosition = *position + *this->_currentVelocity * i_deltaTime;
		position->set(newPosition.X(), newPosition.Y());
	}

	void Rigidbody2D::ComputerResultantLinearAcceleration(float i_deltaTime) const
	{
		const auto velocityAcceleration = *this->_targetVelocity - *this->_currentVelocity;
		const auto accelerationFromForce = *this->_resultantForce / this->_mass;
		const auto gravityAcceleration = *worldPhysicsController->GetGravity() * this->_gravityScale;
		const auto positiveAcceleration = (velocityAcceleration + accelerationFromForce + gravityAcceleration) /
			i_deltaTime;

		this->_currentAcceleration->set(positiveAcceleration.X(), positiveAcceleration.Y());
	}

	void Rigidbody2D::AddForce(Math::Point2D& i_force) const
	{
		const Math::Point2D newForce = *this->_resultantForce + i_force;
		this->_resultantForce->set(newForce.X(), newForce.Y());
	}

#pragma endregion

#pragma region Force/Rotation

	void Rigidbody2D::ComputeResultantAngularAcceleration(const float i_deltaTime)
	{
		const auto angularAcceleration = (this->_targetAngularVelocity - this->_currentAngularVelocity) / i_deltaTime;
		this->_currentAngularAcceleration = angularAcceleration;
	}

	void Rigidbody2D::ApplyAngularVelocityAndAcceleration(const float i_deltaTime)
	{
		// Angular Motion
		auto newAngularVelocity = this->_currentAngularVelocity + this->_currentAngularAcceleration * i_deltaTime;
		if (this->_angularDrag > 1)
		{
			newAngularVelocity = 0;
		}
		else
		{
			newAngularVelocity -= (this->_angularDrag * newAngularVelocity);
		}
		this->_currentAngularVelocity = newAngularVelocity;

		// Apply Rotation
		this->_rotate2d->Rotate(this->_currentAngularVelocity * i_deltaTime);
	}

	void Rigidbody2D::AddForceAtPosition(Math::Point2D& i_force, Math::Point2D& i_position)
	{
		const Math::Point2D p = *this->_node2d->GetPosition() - i_position;
		const float angle = atan2(p.X(), p.Y()) - atan2(i_force.X(), i_force.Y());
		const float t = p.length() * i_force.length() * sin(angle) * Utils::MathUtils::Rad2Deg;

		this->_targetAngularVelocity += t;
	}

#pragma endregion
}
