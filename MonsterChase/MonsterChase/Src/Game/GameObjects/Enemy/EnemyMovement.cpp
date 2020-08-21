#include "EnemyMovement.h"
#include "Src/Maths/Point2D.h"
#include "Src/Utils/Random.h"

#include <cassert>

#include "Src/Utils/Debug.h"

namespace Game::GameObjects::Enemy
{
#pragma region Constructor

	EnemyMovement::EnemyMovement()
	{
		this->_startPosition = new Math::Point2D();
		this->_targetPosition = new Math::Point2D();
		this->_idleStartPosition = new Math::Point2D();
		this->_lerpAmount = 0;

		this->_enemyTimer = 0;
		this->_isUpward = true;
		this->_enemyState = EnemyState::Idle;
	}

#pragma endregion

#pragma region Overridden Parent

	EnemyMovement::~EnemyMovement()
	{
		delete this->_startPosition;
		delete this->_targetPosition;
		delete this->_idleStartPosition;
	}

	void EnemyMovement::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		auto node2d = i_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		assert(node2d);
		this->_node2d = node2d.Lock();

		SetupEnemyIdleMovement();
		SetEnemyState(EnemyState::Idle);
	}

	void EnemyMovement::Process(float i_deltaTime)
	{
		switch (_enemyState)
		{
		case EnemyState::Idle:
			UpdateEnemyIdleState(i_deltaTime);
			break;

		case EnemyState::Moving:
			UpdateEnemyMovementState(i_deltaTime);
			break;

		default:
			// Don't do anything here...
			break;
		}
	}

#pragma endregion

#pragma region Utility Functions

	void EnemyMovement::UpdateEnemyIdleState(const float i_deltaTime)
	{
		this->_enemyTimer -= i_deltaTime;
		if (this->_enemyTimer <= 0)
		{
			this->_enemyTimer = Utils::Random::RandomInRangeF(EnemyMovement::MinMovementTime,
			                                                  EnemyMovement::MaxMovementTime);

			SetRandomMovementPoint();
			SetEnemyState(EnemyState::Moving);

			return;
		}

		this->_lerpAmount += EnemyMovement::IdleLerpSpeed * i_deltaTime;
		const Math::Point2D mappedPosition = Math::Point2D::lerp(*this->_startPosition,
		                                                         *this->_targetPosition,
		                                                         this->_lerpAmount);
		this->_node2d->GetPosition()->set(mappedPosition);

		if (this->_lerpAmount >= 1)
		{
			Math::Point2D* position = this->_node2d->GetPosition();
			this->_startPosition->set(position->X(), position->Y());
			this->_lerpAmount = 0;

			if (this->_isUpward)
			{
				const Math::Point2D newPosition = *this->_idleStartPosition +
					Math::Point2D(0, EnemyMovement::IdleHeight);
				this->_targetPosition->set(newPosition.X(), newPosition.Y());
			}
			else
			{
				const Math::Point2D newPosition = *this->_idleStartPosition -
					Math::Point2D(0, EnemyMovement::IdleHeight);
				this->_targetPosition->set(newPosition.X(), newPosition.Y());
			}

			this->_isUpward = !this->_isUpward;
		}
	}

	void EnemyMovement::SetupEnemyIdleMovement()
	{
		Math::Point2D* position = this->_node2d->GetPosition();
		this->_idleStartPosition->set(position->X(), position->Y());
		this->_startPosition->set(position->X(), position->Y());
		this->_enemyTimer = Utils::Random::RandomInRangeF(EnemyMovement::MinIdleTime,
		                                                  EnemyMovement::MaxIdleTime);

		const float randomValue = Utils::Random::RandomValue();
		if (randomValue <= 0.5f)
		{
			this->_isUpward = true;
			const Math::Point2D newPosition = *this->_idleStartPosition -
				Math::Point2D(0, EnemyMovement::IdleHeight);
			this->_targetPosition->set(newPosition.X(), newPosition.Y());
		}
		else
		{
			this->_isUpward = false;
			const Math::Point2D newPosition = *this->_idleStartPosition +
				Math::Point2D(0, EnemyMovement::IdleHeight);
			this->_targetPosition->set(newPosition.X(), newPosition.Y());
		}
	}

	void EnemyMovement::UpdateEnemyMovementState(const float i_deltaTime)
	{
		this->_enemyTimer -= i_deltaTime;
		if (this->_enemyTimer <= 0)
		{
			this->_enemyTimer = Utils::Random::RandomInRangeF(EnemyMovement::MinIdleTime,
			                                                  EnemyMovement::MaxIdleTime);

			SetupEnemyIdleMovement();
			SetEnemyState(EnemyState::Idle);
			return;
		}

		this->_lerpAmount += EnemyMovement::MovementLerpSpeed * i_deltaTime;
		if (this->_lerpAmount >= 1)
		{
			SetRandomMovementPoint();
		}

		const Math::Point2D mappedPosition = Math::Point2D::lerp(*this->_startPosition,
		                                                         *this->_targetPosition,
		                                                         this->_lerpAmount);
		this->_node2d->GetPosition()->set(mappedPosition);
	}

	void EnemyMovement::SetRandomMovementPoint()
	{
		const float randomX = Utils::Random::RandomInRangeF(EnemyMovement::MinMovementX,
		                                                    EnemyMovement::MaxMovementX);
		const float randomY = Utils::Random::RandomInRangeF(EnemyMovement::MinMovementY,
		                                                    EnemyMovement::MaxMovementY);

		Math::Point2D* position = this->_node2d->GetPosition();
		this->_startPosition->set(position->X(), position->Y());
		this->_targetPosition->set(randomX, randomY);
		this->_lerpAmount = 0;
	}

	void EnemyMovement::SetEnemyState(const EnemyState i_enemyState)
	{
		this->_enemyState = i_enemyState;
	}

#pragma endregion
}
