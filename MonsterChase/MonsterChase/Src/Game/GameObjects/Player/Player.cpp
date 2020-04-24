#include "Player.h"
#include "PlayerShooting.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Maths/Point2D.h"
#include "Src/Core/Controllers/CoreLoop.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "../../Commands/Command.h"
#include "Src/Core/Controllers/GameObjectUpdater.h"
#include "Src/Core/Controllers/GameObjectUpdater_Extern.h"
#include "Src/Core/Components/Physics/Colliders/RectangleCollider.h"
#include "Src/Utils/Debug.h"
#include "Src/Utils/Random.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <string>
#include <functional>

namespace Game::GameObjects::Player
{
#pragma region Constructor And Destructor

	Player::Player() = default;

	Player::~Player()
	{
		gameObjectUpdater->RemoveGameObject(this->_player);
	}

#pragma endregion

#pragma region LifeCycle Functions

	void Player::Init(const Containers::SmartPtr<Commands::InputHandler> i_inputHandler)
	{
		auto* const playerGameObject = new Core::BaseComponents::Node("MainPlayer");
		this->_player = playerGameObject->GetSmartPointerRef();
		this->_inputHandler = i_inputHandler;

		auto node2d = this->_player->AddComponent<Core::Components::Transform::Node2D>();
		this->_player->AddComponent<Core::Components::Transform::Rotate2D>();
		this->_player->AddComponent<Core::Components::Transform::Scale2D>();
		auto renderer = this->_player->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		auto rb = this->_player->AddComponent<Core::Components::Physics::Rigidbody2D>();
		auto playerMovement = this->_player->AddComponent<PlayerMovement>();
		const auto playerShooting = this->_player->AddComponent<PlayerShooting>();

		const std::function<void(Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider>)>
			collisionFunction =
				std::bind(&Player::HandlePlayerCollided, this, std::placeholders::_1);
		this->_player->SetCollisionCallback(collisionFunction);

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
		this->_playerMovement->SetSpriteSize(width, height);

		auto playerCollider = this->_player->AddComponent<Core::Components::Physics::Colliders::RectangleCollider>();
		playerCollider.Lock()->AddToWorld();
	}

	void Player::Update(float i_deltaTime)
	{
		auto commands = this->_inputHandler->CollectCommands(i_deltaTime);
		for (auto& command : commands)
		{
			command->Execute(this->_player);
		}
	}

	void Player::HandlePlayerCollided(
		Containers::WeakPtr<Core::Components::Physics::Colliders::BaseCollider>)
	{
		Utils::Debug::LogOutputToWindow("Player Collided. %g\n", Utils::Random::RandomInRange(0, 100));
	}

#pragma endregion
}
