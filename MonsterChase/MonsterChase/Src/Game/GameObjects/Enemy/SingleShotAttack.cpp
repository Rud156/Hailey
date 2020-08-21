#include "SingleShotAttack.h"
#include "../../Utils/GameConfig.h"
#include "../Common/Projectile.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Containers/SmartPtr.h"
#include "Src/Containers/WeakPtr.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Core/Components/Transform/Node2D.h"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Transform/Scale2D.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Maths/Point2D.h"
#include "Src/Utils/Debug.h"

#include <SFML/Graphics.hpp>

#include <cassert>

namespace Game::GameObjects::Enemy
{
#pragma region Attack Functions

	void SingleShotAttack::LaunchAttack()
	{
		::Utils::Debug::LogOutputToWindow("Starting Single Shot Attack\n");

		this->_currentTimer = 0;
		this->_currentIndex = 0;
	}

	void SingleShotAttack::UpdateAttack(std::vector<Math::Point2D>,
	                                    std::vector<Math::Point2D> i_outerShootingOffsets, const float i_deltaTime)
	{
		this->_currentTimer -= i_deltaTime;
		if (this->_currentTimer <= 0)
		{
			this->_currentTimer = SingleShotAttack::TimeBetweenShots;

			if (this->_currentIndex >= i_outerShootingOffsets.size())
			{
				this->_currentIndex = 0;
			}

			::Utils::Debug::LogOutputToWindow("Launching Single Shot Attack\n");

			Math::Point2D shootingPosition = i_outerShootingOffsets[this->_currentIndex];
			this->_currentIndex += 1;
			Shoot(shootingPosition);
		}
	}


	void SingleShotAttack::EndAttack()
	{
		::Utils::Debug::LogOutputToWindow("Single Shot Attack Ended\n");
	}

#pragma endregion

#pragma region Utility Functions

	void SingleShotAttack::Shoot(Math::Point2D& i_offsetPosition)
	{
		auto* const projectileGameObject = new Core::BaseComponents::Node("EnemyProj");
		projectileGameObject->SetTag(Utils::GameConfig::EnemyProjTag);
		auto node2d = projectileGameObject->AddComponent<Core::Components::Transform::Node2D>();
		projectileGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		auto scale2d = projectileGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = projectileGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		projectileGameObject->AddComponent<Core::Components::Physics::Rigidbody2D>();
		auto projectile = projectileGameObject->AddComponent<Common::Projectile>();

		assert(node2d);
		assert(scale2d);
		assert(renderer);

		auto enemyNode2D = this->_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		auto* const enemyPosition = enemyNode2D.Lock()->GetPosition();
		const auto shootingPosition = *enemyPosition + i_offsetPosition;
		node2d.Lock()->GetPosition()->set(shootingPosition.X(), shootingPosition.Y());

		scale2d.Lock()->GetScale()->set(0.75f, 0.75f);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/Bullet.png";
		renderer.Lock()->LoadTexture(filePath);
		auto* sprite = renderer.Lock()->GetSprite();
		sprite->setColor(sf::Color::Magenta);

		const float xVelocity = 0;
		const float yVelocity = 1;
		projectile.Lock()->LaunchProjectile(new Math::Point2D(xVelocity, yVelocity));
		projectile.Lock()->SetDamageAmount(Utils::GameConfig::EnemyProjectileDamage);

		auto projectileCollider = projectileGameObject->
			AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		auto colliderInstance = projectileCollider.Lock();
		colliderInstance->SetGroupIndex(Utils::GameConfig::EnemyGroup);
		colliderInstance->SetCategoryBits(Utils::GameConfig::EnemyProjectileCat);
		colliderInstance->SetMaskBits(Utils::GameConfig::PlayerCat);
	}

#pragma endregion
}
