#pragma once
#include "../../BaseComponents/Component.h"
#include "../../../Containers/SmartPtr.h"
#include "../../../Containers/WeakPtr.h"
#include "../Transform/Node2D.h"
#include "../Transform/Rotate2D.h"


namespace Math
{
	class Point2D;
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

				float _currentAngularVelocity;
				float _targetAngularVelocity;
				float _currentAngularAcceleration;

				Containers::SmartPtr<Transform::Node2D> _node2d{};
				Containers::SmartPtr<Transform::Rotate2D> _rotate2d{};
				float _mass{1};
				float _linearDrag{};
				float _angularDrag{};

				float _gravityScale{1};

				void ResetBodyForcesData();
				void ComputerResultantLinearAcceleration(float i_deltaTime) const;
				void ApplyLinearVelocityAndAcceleration(float i_deltaTime);

				void ComputeResultantAngularAcceleration(float i_deltaTime);
				void ApplyAngularVelocityAndAcceleration(float i_deltaTime);

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
				Math::Point2D* GetVelocity() const;
				void SetAngularVelocity(float i_angularVelocity);
				float GetAngularVelocity() const;

				// Force
				void AddForceAtPosition(Math::Point2D& i_force, Math::Point2D& i_position);
				void AddForce(Math::Point2D& i_force) const;

				// Parent Overrides
				void Ready(Containers::WeakPtr<BaseComponents::Node> i_node) override;
				void PhysicsProcess(float i_fixedDeltaTime) override;
			};
		}
	}
}
