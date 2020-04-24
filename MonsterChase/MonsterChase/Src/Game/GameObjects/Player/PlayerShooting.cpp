#include "PlayerShooting.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Utils/MathUtils.h"
#include "Src/Core/Components/Physics/Rigidbody2D.h"
#include "Src/Maths/Point2D.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Core/Loaders/FileLoader.h"
#include "Src/Core/Components/Transform/Scale2D.h"

#include <cassert>
#include <cmath>
#include <string>

#include "../Common/Projectile.h"

namespace Game::GameObjects::Player
{
#pragma region Constructor

	PlayerShooting::PlayerShooting()
	{
		this->_launchOffset = new Math::Point2D(0, -27);
		this->_shootingTimer = 0;
	}

#pragma endregion

#pragma region Shooting Functions

	void PlayerShooting::Shoot()
	{
		if (_shootingTimer > 0)
		{
			return;
		}

		_shootingTimer = ShootDelay;

		auto* const projectileGameObject = new Core::BaseComponents::Node("PlayerProj");
		auto projectileRef = projectileGameObject->GetSmartPointerRef();
		auto projectileNode2D = projectileGameObject->AddComponent<Core::Components::Transform::Node2D>();
		auto projectileRotation = projectileGameObject->AddComponent<Core::Components::Transform::Rotate2D>();
		auto projectileScale = projectileGameObject->AddComponent<Core::Components::Transform::Scale2D>();
		auto projectileRenderer = projectileGameObject->AddComponent<Core::Components::Rendering::SpriteRenderer>();
		projectileGameObject->AddComponent<Core::Components::Physics::Rigidbody2D>();
		auto projectile = projectileRef->AddComponent<Common::Projectile>();

		projectileRotation.Lock()->SetAngle(this->_rotate2d->GetAngle());

		auto* const playerPosition = this->_node2d->GetPosition();
		const auto launchPosition = *playerPosition + *this->_launchOffset;
		projectileNode2D.Lock()->GetPosition()->set(launchPosition.X(), launchPosition.Y());

		const float xVelocity = std::sin(this->_rotate2d->GetAngle() * Utils::MathUtils::Deg2Rad);
		const float yVelocity = -std::cos(this->_rotate2d->GetAngle() * Utils::MathUtils::Deg2Rad);
		projectile.Lock()->LaunchProjectile(new Math::Point2D(xVelocity, yVelocity));

		projectileScale.Lock()->GetScale()->set(0.75f, 0.75f);

		std::string filePath = Core::Loaders::FileLoader::Assets;
		filePath += "/Images/Bullet.png";
		projectileRenderer.Lock()->LoadTexture(filePath);
	}

#pragma endregion

#pragma region Parent Overrides

	PlayerShooting::~PlayerShooting()
	{
		delete this->_launchOffset;
	}

	void PlayerShooting::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		Containers::WeakPtr<Core::Components::Transform::Node2D> node2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		Containers::WeakPtr<Core::Components::Transform::Rotate2D> rotate2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Rotate2D>();

		assert(node2d);
		assert(rotate2d);

		this->_node2d = node2d.Lock();
		this->_rotate2d = rotate2d.Lock();
	}

	void PlayerShooting::Process(float i_deltaTime)
	{
		_shootingTimer -= i_deltaTime;
	}

#pragma endregion
}
