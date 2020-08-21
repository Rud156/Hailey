#pragma once
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Core/Components/Transform/Node2D.h"

namespace Math
{
	class Point2D;
}

namespace Game::GameObjects::Enemy
{
	class EnemyMovement final : public Core::BaseComponents::Component
	{
	private:
		enum class EnemyState
		{
			Idle,
			Moving
		};

		static const inline float MinIdleTime = 3.0f;
		static const inline float MaxIdleTime = 7.0f;
		static const inline float IdleHeight = 30.0f;
		static const inline float IdleLerpSpeed = 0.5f;

		static const inline float MinMovementTime = 7.0f;
		static const inline float MaxMovementTime = 14.0f;
		static const inline float MovementLerpSpeed = 0.55f;
		static const inline float MinMovementX = 150.0f;
		static const inline float MaxMovementX = 450.0f;
		static const inline float MinMovementY = 200.0f;
		static const inline float MaxMovementY = 400.0f;

		Containers::SmartPtr<Core::Components::Transform::Node2D> _node2d;

		float _enemyTimer;
		EnemyState _enemyState;

		// Movement/Idling
		Math::Point2D* _startPosition;
		Math::Point2D* _targetPosition;
		float _lerpAmount;

		// Idling
		bool _isUpward;
		Math::Point2D* _idleStartPosition;

		// Utility Functions
		void UpdateEnemyIdleState(float i_deltaTime);
		void SetupEnemyIdleMovement();
		void UpdateEnemyMovementState(float i_deltaTime);
		void SetRandomMovementPoint();
		void SetEnemyState(EnemyState i_enemyState);

	public:
		// Constructor
		EnemyMovement();

		// Overridden Parent
		~EnemyMovement();
		virtual void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;
		virtual void Process(float i_deltaTime) override;
	};
}
