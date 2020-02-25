#pragma once
#include "Component.h"

namespace Math
{
	class Point2D;
}

namespace Core
{
	namespace Components
	{
		namespace Transform
		{
			class Node2D;
			class Rotate2D;
		}
	}
}

namespace Core
{
	namespace Components
	{
		namespace Physics
		{
			// TODO: Calculate Inertia Based on the Collider Type https://github.com/erincatto/box2d/blob/f683bc4a5106d813d473b4e797c3d782169ed30e/src/collision/b2_circle_shape.cpp
			// TODO: Implement Lerping For Sprites
			class Rigidbody2D final : public BaseComponents::Component
			{
			private:
				Math::Point2D* _currentVelocity;
				Math::Point2D* _targetVelocity;
				Math::Point2D* _currentAcceleration;
				Math::Point2D* _resultantForce;

				float _angularVelocity;

				Transform::Node2D* _node2d{};
				Transform::Rotate2D* _rotate2d{};
				float _mass{1};
				float _linearDrag{};
				float _angularDrag{};

				float _gravityScale{1};

				void ResetBodyForcesData() const;
				void ApplyVelocityAndAcceleration(float i_deltaTime);
				void ComputerResultantAcceleration() const;

			public:
				// Constructor and Destructor
				Rigidbody2D();
				~Rigidbody2D();

				// Setters
				void SetMass(float i_mass);
				void SetLinearDrag(float i_linearDrag);
				void SetAngularDrag(float i_angularDrag);
				void SetGravityScale(float i_gravityScale);

				// Velocity
				void SetVelocity(float i_x, float i_y) const;
				void SetVelocity(Math::Point2D& velocity) const;
				void SetAngularVelocity(float i_angularVelocity);

				// Force
				void AddForceAtPosition(Math::Point2D& i_force, Math::Point2D& i_position);
				void AddForce(Math::Point2D& i_force) const;

				// Parent Overrides
				void Ready(BaseComponents::Node* i_node) override;
				void PhysicsProcess(float i_fixedDeltaTime) override;
			};
		}
	}
}
