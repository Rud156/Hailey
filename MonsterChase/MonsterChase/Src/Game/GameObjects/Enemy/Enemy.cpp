#include "Enemy.h"
#include "DualShotAttack.h"
#include "EnemyMovement.h"
#include "SingleShotAttack.h"
#include "SprayShotAttack.h"
#include "../../Utils/GameConfig.h"
#include "../Common/Projectile.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Containers/SmartPtr.h"
#include "Src/Core/BaseComponents/Node.h"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Transform/Scale2D.h"
#include "Src/Core/Controllers/CoreLoop.h"
#include "Src/Core/Controllers/GameObjectUpdater_Extern.h"
#include "Src/Core/Controllers/LoopTimer.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Maths/Point2D.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <functional>
#include <string>

#include "../Common/HealthDisplay.h"
#include "Src/Utils/MathUtils.h"

namespace Game::GameObjects::Enemy
{
#pragma region Constructor and Destructor

	Enemy::Enemy()
	{
		this->_currentHealth = 0;
	}

	Enemy::~Enemy() = default;

#pragma endregion

#pragma region LifeCycle Functions

	void Enemy::Init()
	{
		auto* enemyGameObject = new Core::BaseComponents::Node("EnemyBoss");
		enemyGameObject->SetTag(Utils::GameConfig::EnemyTag);
		auto node2d = enemyGameObject->AddComponent<Core::Components::Transform::Node2D>();
		const auto rotate2d = enemyGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		auto scale2d = enemyGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = enemyGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		const auto singleShotAttack = enemyGameObject->AddComponent<SingleShotAttack>();
		const auto dualShotAttack = enemyGameObject->AddComponent<DualShotAttack>();
		const auto sprayShotAttack = enemyGameObject->AddComponent<SprayShotAttack>();
		const auto attackController = enemyGameObject->AddComponent<EnemyAttackController>();

		assert(node2d);
		assert(rotate2d);
		assert(scale2d);
		assert(renderer);
		assert(singleShotAttack);
		assert(dualShotAttack);
		assert(sprayShotAttack);
		assert(attackController);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/EnemyShip.png";

		renderer.Lock()->LoadTexture(filePath);
		auto* const enemySprite = renderer.Lock()->GetSprite();

		const float spriteHeight = static_cast<float>(enemySprite->getTexture()->getSize().y);
		const float screenWidth = static_cast<float>(Core::Controllers::CoreLoop::Window->getSize().x);

		node2d.Lock()->GetPosition()->set(screenWidth / 2.0f, spriteHeight + 50);
		scale2d.Lock()->GetScale()->set(2, 2);

		const auto enemyMovement = enemyGameObject->AddComponent<EnemyMovement>();
		assert(enemyMovement);

		auto collider = enemyGameObject->AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		assert(collider);
		auto colliderRef = collider.Lock();
		colliderRef->SetGroupIndex(Utils::GameConfig::EnemyGroup);
		colliderRef->SetCategoryBits(Utils::GameConfig::EnemyCat);
		colliderRef->SetMaskBits(Utils::GameConfig::PlayerCat | Utils::GameConfig::PlayerProjectileCat);
		const std::function<void(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider>,
		                         Math::Point2D)> collisionFunction =
			std::bind(&Enemy::HandleEnemyCollided, this, std::placeholders::_1, std::placeholders::_2);
		enemyGameObject->SetCollisionCallback(collisionFunction);
		enemyGameObject->SetTag(Utils::GameConfig::EnemyTag);

		this->_currentHealth = Enemy::MaxHealth;
		this->_enemyAttackController = attackController;

		SetupEnemyHealthDisplay();
	}

	void Enemy::Update(float)
	{
	}

#pragma endregion

#pragma region Utility Functions

	// Note: this function is called per deltaTime
	void Enemy::HandleEnemyCollided(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider> i_collider,
	                                Math::Point2D)
	{
		if (i_collider.Lock()->GetNode().Lock()->GetTag() == Utils::GameConfig::PlayerProjTag)
		{
			const float damageAmount = i_collider.Lock()->GetNode().Lock()->GetComponent<Common::Projectile>().Lock()->
			                                      GetDamageAmount();

			this->_currentHealth -= damageAmount;
			gameObjectUpdater->RemoveGameObject(i_collider.Lock()->GetNode().Lock());

			UpdateEnemyHealth();
		}
	}

	void Enemy::SetupEnemyHealthDisplay()
	{
		auto* const healthGameObject = new Core::BaseComponents::Node("EnemyHealth");

		auto node2d = healthGameObject->AddComponent<Core::Components::Transform::Node2D>();
		healthGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		auto scale = healthGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = healthGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		auto healthDisplay = healthGameObject->AddComponent<Common::HealthDisplay>();

		this->_healthDisplay = healthDisplay.Lock();
		this->_healthDisplay->SetXScaleRatio(18.5f);
		scale.Lock()->GetScale()->set(18.5, 0.5f);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/WhitePixel.png";

		node2d.Lock()->GetPosition()->set(0.0f, 5.0f);

		renderer.Lock()->LoadTexture(filePath);
		auto* displaySprite = renderer.Lock()->GetSprite();
		const float width = static_cast<float>(displaySprite->getTexture()->getSize().x);
		const float height = static_cast<float>(displaySprite->getTexture()->getSize().y);
		renderer.Lock()->GetSprite()->setOrigin(0, height / 2.0f);
	}

	void Enemy::UpdateEnemyHealth()
	{
		float healthRatio = this->_currentHealth / Enemy::MaxHealth;
		healthRatio = ::Utils::MathUtils::Clamp(healthRatio, 0.0f, 1.0f);
		if (healthRatio <= Enemy::EnemyLowHealthPercent)
		{
			this->_enemyAttackController.Lock()->ActivateEnemyLowHealthMode();
		}

		this->_healthDisplay->UpdateHealthDisplay(healthRatio);

		if (this->_currentHealth <= 0)
		{
			this->_enemyAttackController.Lock()->DeActivateEnemyAttacks();
		}
	}

#pragma endregion
}
