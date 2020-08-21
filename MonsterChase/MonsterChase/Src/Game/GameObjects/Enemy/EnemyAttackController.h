#pragma once
#include "DualShotAttack.h"
#include "SingleShotAttack.h"
#include "SprayShotAttack.h"
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Component.h"
#include "Src/Maths/Point2D.h"

#include <vector>

namespace Game::GameObjects::Enemy
{
	class EnemyAttackController final : public Core::BaseComponents::Component
	{
	private:
		enum class EnemyAttackState
		{
			Idle = 0,
			SingleShot = 1,
			DualShot = 2,
			Spray = 3
		};

		static const inline float MinIdleTime = 1;
		static const inline float MaxIdleTime = 3;

		static const inline float MinAttackTime = 7;
		static const inline float MaxAttackTime = 14;

		static const inline float SprayAttackChance = 0.75f;

		std::vector<Math::Point2D> _outerShootingOffsets;
		std::vector<Math::Point2D> _innerShootingOffsets;
		Math::Point2D _centerShootingOffset;

		Containers::SmartPtr<SingleShotAttack> _singleShotAttack;
		Containers::SmartPtr<DualShotAttack> _dualShotAttack;
		Containers::SmartPtr<SprayShotAttack> _sprayShotAttack;

		bool _hasLowHealth;
		bool _isDisabled;

		float _enemyAttackTimer;
		EnemyAttackState _enemyAttackState;

		// Utility Functions
		void UpdateAttackIdleState(float i_deltaTime);
		void UpdateSingleShotAttackState(float i_deltaTime);
		void UpdateDualShotAttackState(float i_deltaTime);
		void UpdateSprayShotAttackState(float i_deltaTime);
		void SetEnemyAttackState(EnemyAttackState i_enemyAttackState);

	public:
		// Constructor
		EnemyAttackController();

		// Overridden Parent
		virtual void Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node) override;
		virtual void Process(float i_deltaTime) override;
		virtual void Exit() override;

		// External Functions
		void ActivateEnemyLowHealthMode();
		void DeActivateEnemyAttacks();
	};
}
