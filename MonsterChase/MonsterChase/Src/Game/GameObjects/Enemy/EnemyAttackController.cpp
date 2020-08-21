#include "EnemyAttackController.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Utils/Debug.h"
#include "Src/Utils/Random.h"

namespace Game::GameObjects::Enemy
{
#pragma region Constructor

	EnemyAttackController::EnemyAttackController()
	{
		this->_enemyAttackState = EnemyAttackState::Idle;
		this->_enemyAttackTimer = 0;
		this->_hasLowHealth = false;
		this->_isDisabled = false; // TODO: Change this later on...
	}

#pragma endregion

#pragma region Overridden Parent

	void EnemyAttackController::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		this->_innerShootingOffsets.insert(this->_innerShootingOffsets.end(), {
			                                   Math::Point2D(-44, 66),
			                                   Math::Point2D(44, 66)
		                                   });
		this->_outerShootingOffsets.insert(this->_outerShootingOffsets.end(), {
			                                   Math::Point2D(-86, 80),
			                                   Math::Point2D(86, 80)
		                                   });
		this->_centerShootingOffset = Math::Point2D(0, 66);

		auto singleShotAttack = i_node.Lock()->GetComponent<SingleShotAttack>();
		auto dualShotAttack = i_node.Lock()->GetComponent<DualShotAttack>();
		auto sprayShotAttack = i_node.Lock()->GetComponent<SprayShotAttack>();

		assert(singleShotAttack);
		assert(dualShotAttack);
		assert(sprayShotAttack);

		this->_singleShotAttack = singleShotAttack.Lock();
		this->_dualShotAttack = dualShotAttack.Lock();
		this->_sprayShotAttack = sprayShotAttack.Lock();

		this->_enemyAttackTimer = Utils::Random::RandomInRangeF(EnemyAttackController::MinIdleTime,
		                                                        EnemyAttackController::MaxIdleTime);
		SetEnemyAttackState(EnemyAttackState::Idle);
	}

	void EnemyAttackController::Process(float i_deltaTime)
	{
		if (this->_isDisabled)
		{
			return;
		}

		switch (this->_enemyAttackState)
		{
		case EnemyAttackState::Idle:
			UpdateAttackIdleState(i_deltaTime);
			break;

		case EnemyAttackState::SingleShot:
			UpdateSingleShotAttackState(i_deltaTime);
			break;

		case EnemyAttackState::DualShot:
			UpdateDualShotAttackState(i_deltaTime);
			break;

		case EnemyAttackState::Spray:
			UpdateSprayShotAttackState(i_deltaTime);
			break;

		default:
			// Don't do anything here...
			break;
		}
	}

	void EnemyAttackController::Exit()
	{
		this->_innerShootingOffsets.clear();
		this->_outerShootingOffsets.clear();
	}

#pragma endregion

#pragma region External Functions

	void EnemyAttackController::ActivateEnemyLowHealthMode()
	{
		this->_hasLowHealth = true;
	}

	void EnemyAttackController::DeActivateEnemyAttacks()
	{
		this->_isDisabled = true;
	}

#pragma endregion

#pragma region Utility Functions

	void EnemyAttackController::UpdateAttackIdleState(float i_deltaTime)
	{
		this->_enemyAttackTimer -= i_deltaTime;
		if (this->_enemyAttackTimer <= 0)
		{
			bool isSpray = false;
			if (this->_hasLowHealth)
			{
				isSpray = Utils::Random::RandomValue() <= EnemyAttackController::SprayAttackChance ? true : false;
			}

			int randomNumber = Utils::Random::RandomInRange(1, 2);
			auto attackState = static_cast<EnemyAttackState>(randomNumber);
			if (isSpray)
			{
				attackState = EnemyAttackState::Spray;
			}
			SetEnemyAttackState(attackState);

			this->_enemyAttackTimer = Utils::Random::RandomInRangeF(EnemyAttackController::MinAttackTime,
			                                                        EnemyAttackController::MaxAttackTime);

			// This may not be required.
			// Not sure if attacks starting and ending is required
			switch (attackState)
			{
			case EnemyAttackState::SingleShot:
				this->_singleShotAttack->LaunchAttack();
				break;

			case EnemyAttackState::DualShot:
				this->_dualShotAttack->LaunchAttack();
				break;

			case EnemyAttackState::Spray:
				this->_sprayShotAttack->LaunchAttack();
				break;

			default:
				Utils::Debug::LogOutputToWindow("Invalid State Generated\n");
				assert(false);
				// Don't do anything here...
				break;
			}
		}
	}

	void EnemyAttackController::UpdateSingleShotAttackState(const float i_deltaTime)
	{
		this->_enemyAttackTimer -= i_deltaTime;
		if (this->_enemyAttackTimer <= 0)
		{
			this->_singleShotAttack->EndAttack();
			this->_enemyAttackTimer = Utils::Random::RandomInRangeF(EnemyAttackController::MinIdleTime,
			                                                        EnemyAttackController::MaxIdleTime);

			SetEnemyAttackState(EnemyAttackState::Idle);
		}
		else
		{
			this->_singleShotAttack->UpdateAttack(this->_innerShootingOffsets,
			                                      this->_outerShootingOffsets,
			                                      i_deltaTime);
		}
	}

	void EnemyAttackController::UpdateDualShotAttackState(float i_deltaTime)
	{
		this->_enemyAttackTimer -= i_deltaTime;
		if (this->_enemyAttackTimer <= 0)
		{
			this->_dualShotAttack->EndAttack();
			this->_enemyAttackTimer = Utils::Random::RandomInRangeF(EnemyAttackController::MinIdleTime,
			                                                        EnemyAttackController::MaxIdleTime);

			SetEnemyAttackState(EnemyAttackState::Idle);
		}
		else
		{
			this->_dualShotAttack->UpdateAttack(this->_innerShootingOffsets,
			                                    this->_outerShootingOffsets,
			                                    i_deltaTime);
		}
	}

	void EnemyAttackController::UpdateSprayShotAttackState(float i_deltaTime)
	{
		this->_enemyAttackTimer -= i_deltaTime;
		if (this->_enemyAttackTimer <= 0)
		{
			this->_sprayShotAttack->EndAttack();
			this->_enemyAttackTimer = Utils::Random::RandomInRangeF(EnemyAttackController::MinIdleTime,
			                                                        EnemyAttackController::MaxIdleTime);

			SetEnemyAttackState(EnemyAttackState::Idle);
		}
		else
		{
			this->_sprayShotAttack->UpdateAttack(this->_centerShootingOffset, i_deltaTime);
		}
	}

	void EnemyAttackController::SetEnemyAttackState(const EnemyAttackState i_enemyAttackState)
	{
		this->_enemyAttackState = i_enemyAttackState;
	}

#pragma endregion
}
