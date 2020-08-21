#include "SprayShotAttack.h"
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
#include "Src/Utils/MathUtils.h"
#include "Src/Utils/Random.h"

#include <SFML/Graphics.hpp>

#include <cassert>

namespace Game::GameObjects::Enemy
{
#pragma region Attack Functions

	void SprayShotAttack::LaunchAttack()
	{
		::Utils::Debug::LogOutputToWindow("Starting Spray Shot Attacks\n");

		this->_currentTimer = 0;
		this->_currentAngle = 0;
	}

	void SprayShotAttack::UpdateAttack(Math::Point2D& i_centerPosition, const float i_deltaTime)
	{
		this->_currentTimer -= i_deltaTime;
		if (this->_currentTimer <= 0)
		{
			Shoot(i_centerPosition, this->_currentAngle);

			this->_currentTimer = SprayShotAttack::TimeBetweenShots;
			this->_currentAngle += SprayShotAttack::AngleIncrementAmount;
			this->_currentAngle = ::Utils::MathUtils::To360Deg(this->_currentAngle);
		}
	}

	void SprayShotAttack::EndAttack()
	{
		::Utils::Debug::LogOutputToWindow("Spray Shot Attack Ended\n");
	}

#pragma endregion

#pragma region Utility Functions

	void SprayShotAttack::Shoot(Math::Point2D& i_offsetPosition, const float i_angle)
	{
		auto* const projectileGameObject = new Core::BaseComponents::Node("EnemyProj");
		projectileGameObject->SetTag(Utils::GameConfig::EnemyProjTag);
		auto node2d = projectileGameObject->AddComponent<Core::Components::Transform::Node2D>();
		auto rotate2d = projectileGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		const auto scale2d = projectileGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = projectileGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		projectileGameObject->AddComponent<Core::Components::Physics::Rigidbody2D>();
		auto projectile = projectileGameObject->AddComponent<Common::Projectile>();

		assert(node2d);
		assert(rotate2d);
		assert(scale2d);
		assert(renderer);

		rotate2d.Lock()->SetAngle(i_angle);

		auto enemyNode2D = this->_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		auto* const enemyPosition = enemyNode2D.Lock()->GetPosition();
		const auto shootingPosition = *enemyPosition + i_offsetPosition;
		node2d.Lock()->GetPosition()->set(shootingPosition.X(), shootingPosition.Y());

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/Bullet.png";
		renderer.Lock()->LoadTexture(filePath);
		auto* sprite = renderer.Lock()->GetSprite();
		sprite->setColor(sf::Color::Red);

		const float xVelocity = std::sin(i_angle * ::Utils::MathUtils::Deg2Rad);
		const float yVelocity = -std::cos(i_angle * ::Utils::MathUtils::Deg2Rad);
		projectile.Lock()->LaunchProjectile(new Math::Point2D(xVelocity, yVelocity));
		projectile.Lock()->SetDamageAmount(Utils::GameConfig::EnemyLargeProjectileDamage);

		auto projectileCollider = projectileGameObject->
			AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		auto colliderInstance = projectileCollider.Lock();
		colliderInstance->SetGroupIndex(Utils::GameConfig::EnemyGroup);
		colliderInstance->SetCategoryBits(Utils::GameConfig::EnemyProjectileCat);
		colliderInstance->SetMaskBits(Utils::GameConfig::PlayerCat);
	}

#pragma endregion
}
