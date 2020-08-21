#include "Player.h"
#include "PlayerShooting.h"
#include "../../Commands/Command.h"
#include "../../Utils/GameConfig.h"
#include "../Common/Projectile.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Core/Controllers/CoreLoop.h"
#include "Src/Core/Controllers/GameObjectUpdater.h"
#include "Src/Core/Controllers/GameObjectUpdater_Extern.h"
#include "Src/Core/Controllers/LoopTimer.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Maths/Point2D.h"
#include "Src/Utils/Debug.h"
#include "Src/Utils/MathUtils.h"
#include "Src/Utils/Random.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <functional>
#include <string>

namespace Game::GameObjects::Player
{
#pragma region Constructor And Destructor

	Player::Player() = default;

	Player::~Player()
	{
		gameObjectUpdater->RemoveGameObject(this->_player.Lock());
	}

#pragma endregion

#pragma region LifeCycle Functions

	void Player::Init(const Containers::SmartPtr<Commands::InputHandler> i_inputHandler)
	{
		auto* const playerGameObject = new Core::BaseComponents::Node("MainPlayer");
		this->_player = playerGameObject->GetWeakPointerRef();
		this->_inputHandler = i_inputHandler;

		auto node2d = playerGameObject->AddComponent<Core::Components::Transform::Node2D>();
		playerGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		playerGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = playerGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		auto rb = playerGameObject->AddComponent<Core::Components::Physics::Rigidbody2D>();
		auto playerMovement = playerGameObject->AddComponent<PlayerMovement>();
		const auto playerShooting = playerGameObject->AddComponent<PlayerShooting>();

		const std::function<void(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider>,
		                         Math::Point2D)> collisionFunction =
			std::bind(&Player::HandlePlayerCollided, this, std::placeholders::_1, std::placeholders::_2);
		playerGameObject->SetCollisionCallback(collisionFunction);
		playerGameObject->SetTag(Utils::GameConfig::PlayerTag);

		assert(node2d);
		assert(renderer);
		assert(rb);
		assert(playerMovement);
		assert(playerShooting);

		this->_node2d = node2d.Lock();
		this->_playerPosition = this->_node2d->GetPosition();

		this->_playerMovement = playerMovement.Lock();

		this->_playerRb = rb.Lock();
		this->_playerRb->SetGravityScale(0);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/SpaceShip.png";

		renderer.Lock()->LoadTexture(filePath);
		auto* const playerSprite = renderer.Lock()->GetSprite();

		const float width = static_cast<float>(playerSprite->getTexture()->getSize().x);
		const float height = static_cast<float>(playerSprite->getTexture()->getSize().y);
		const float xPosition = Core::Controllers::CoreLoop::Window->getSize().x / 2.0f;
		const float yPosition = static_cast<float>(Core::Controllers::CoreLoop::Window->getSize().y) - 50;

		this->_playerPosition->set(xPosition, yPosition);
		this->_playerMovement->SetSpriteInfo(width, height);

		auto playerCollider = playerGameObject->AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		auto playerColliderInstance = playerCollider.Lock();
		playerColliderInstance->SetGroupIndex(Utils::GameConfig::PlayerGroup);
		playerColliderInstance->SetCategoryBits(Utils::GameConfig::PlayerCat);
		playerColliderInstance->SetMaskBits(Utils::GameConfig::EnemyCat | Utils::GameConfig::EnemyProjectileCat);

		this->_currentHealth = Player::MaxPlayerHealth;

		SetupPlayerHealthDisplay();
	}

	void Player::Update(float i_deltaTime)
	{
		auto commands = this->_inputHandler->CollectCommands(i_deltaTime);
		for (auto& command : commands)
		{
			command->Execute(this->_player.Lock());
		}
	}

#pragma endregion

#pragma region Utility Functions

	void Player::SetupPlayerHealthDisplay()
	{
		auto* const healthGameObject = new Core::BaseComponents::Node("PlayerHealth");

		auto node2d = healthGameObject->AddComponent<Core::Components::Transform::Node2D>();
		healthGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		auto scale = healthGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = healthGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		auto healthDisplay = healthGameObject->AddComponent<Common::HealthDisplay>();

		const float windowHeight = static_cast<float>(Core::Controllers::CoreLoop::Window->getSize().y);

		this->_healthDisplay = healthDisplay.Lock();
		this->_healthDisplay->SetXScaleRatio(18.5f);
		scale.Lock()->GetScale()->set(18.5f, 0.5f);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/WhitePixel.png";

		node2d.Lock()->GetPosition()->set(0.0f, windowHeight - 10);

		renderer.Lock()->LoadTexture(filePath);
		auto* displaySprite = renderer.Lock()->GetSprite();
		const float width = static_cast<float>(displaySprite->getTexture()->getSize().x);
		const float height = static_cast<float>(displaySprite->getTexture()->getSize().y);
		renderer.Lock()->GetSprite()->setOrigin(0, height / 2.0f);
	}

	void Player::HandlePlayerCollided(
		Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider> i_collider,
		Math::Point2D)
	{
		if (i_collider.Lock()->GetNode().Lock()->GetTag() == Utils::GameConfig::EnemyTag)
		{
			this->_currentHealth -= Utils::GameConfig::EnemyDPS *
				static_cast<float>(Core::Controllers::LoopTimer::DeltaTime);
			UpdatePlayerHealth();
		}
		else if (i_collider.Lock()->GetNode().Lock()->GetTag() == Utils::GameConfig::EnemyProjTag)
		{
			const float damageAmount = i_collider.Lock()->GetNode().Lock()->GetComponent<Common::Projectile>().Lock()->
			                                      GetDamageAmount();

			this->_currentHealth -= damageAmount;
			gameObjectUpdater->RemoveGameObject(i_collider.Lock()->GetNode().Lock());

			UpdatePlayerHealth();
		}
	}

	void Player::UpdatePlayerHealth()
	{
		float healthRatio = this->_currentHealth / Player::MaxPlayerHealth;
		healthRatio = ::Utils::MathUtils::Clamp(healthRatio, 0.0f, 1.0f);
		this->_healthDisplay->UpdateHealthDisplay(healthRatio);

		if (this->_currentHealth <= 0)
		{
			::Utils::Debug::LogOutputToWindow("Player Died\n");
		}
	}

#pragma endregion
}
