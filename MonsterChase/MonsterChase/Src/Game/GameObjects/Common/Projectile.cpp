#include "Projectile.h"
#include "Src/Containers/PointerIncludes.cpp"
#include "Src/Core/Components/Transform/Rotate2D.h"
#include "Src/Core/Components/Rendering/SpriteRenderer.h"
#include "Src/Maths/Point2D.h"
#include "Src/Core/Controllers/GameObjectUpdater.h"
#include "Src/Core/Controllers/GameObjectUpdater_Extern.h"

#include <cassert>

namespace Game::GameObjects::Common
{
#pragma region Parent Overrides

	Projectile::Projectile()
	{
		this->_launchDirection = new Math::Point2D();
		this->_currentLifeTime = Projectile::DestroyLifetime;
	}

	Projectile::~Projectile() = default;

	void Projectile::Ready(Containers::WeakPtr<Core::BaseComponents::Node> i_node)
	{
		Component::Ready(i_node);

		Containers::WeakPtr<Core::Components::Transform::Node2D> node2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Node2D>();
		const Containers::WeakPtr<Core::Components::Transform::Rotate2D> rotate2d =
			i_node.Lock()->GetComponent<Core::Components::Transform::Rotate2D>();
		Containers::WeakPtr<Core::Components::Physics::Rigidbody2D> rb =
			i_node.Lock()->GetComponent<Core::Components::Physics::Rigidbody2D>();
		const Containers::WeakPtr<Core::Components::Rendering::SpriteRenderer> renderer =
			i_node.Lock()->GetComponent<Core::Components::Rendering::SpriteRenderer>();

		assert(node2d);
		assert(rotate2d);
		assert(rb);
		assert(renderer);

		this->_node2d = node2d.Lock();
		this->_projectileRb = rb.Lock();
	}

	void Projectile::Process(float i_deltaTime)
	{
		this->_currentLifeTime -= i_deltaTime;
		if (this->_currentLifeTime <= 0)
		{
			DestroyProjectile();
		}
	}

	void Projectile::Exit()
	{
		delete this->_launchDirection;
	}

#pragma endregion

#pragma region External Functions

	void Projectile::LaunchProjectile(Math::Point2D* i_launchDirection)
	{
		this->_launchDirection = i_launchDirection;
		Math::Point2D projectileVelocity = Projectile::ProjectileVelocity * *this->_launchDirection;
		this->_projectileRb->SetVelocity(projectileVelocity);
		this->_currentLifeTime = Projectile::DestroyLifetime;
	}

#pragma endregion

#pragma region Utility Functions

	void Projectile::DestroyProjectile()
	{
		gameObjectUpdater->RemoveGameObject(this->_node.Lock());
	}

#pragma endregion
}
