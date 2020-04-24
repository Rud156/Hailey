#include "CircleCollider.h"
#include "../../../../Maths/Point2D.h"
#include "../../../Components/Rendering/SpriteRenderer.h"
#include "../../../../Containers/PointerIncludes.cpp"

#include <SFML/Graphics.hpp>

namespace Core::Components::Physics::Colliders
{
#pragma region Constructor

	CircleCollider::CircleCollider()
	{
		this->_radius = 1;

		this->_circle = new sf::CircleShape();
		this->_circle->setFillColor(sf::Color::Transparent);
		this->_circle->setOutlineColor(sf::Color::Red);
		this->_circle->setOutlineThickness(1);
	}

#pragma endregion

#pragma region Overridden Parent

	CircleCollider::~CircleCollider()
	{
		delete this->_circle;
	}

	void CircleCollider::Ready(Containers::WeakPtr<BaseComponents::Node> i_node)
	{
		BaseCollider::Ready(i_node);

		this->_colliderType = ColliderType::Circle;
		Containers::WeakPtr<Rendering::SpriteRenderer> renderer =
			i_node.Lock()->GetComponent<Rendering::SpriteRenderer>();

		if (renderer)
		{
			const auto textureSize = renderer.Lock()->GetSprite()->getTexture()->getSize();
			const auto largestSide = static_cast<float>(textureSize.x > textureSize.y ? textureSize.x : textureSize.y);
			this->_radius = largestSide / 2.0f;
		}
	}

	void CircleCollider::SetupRender()
	{
		this->_circle->setPosition(this->_center->X(), this->_center->Y());
		this->_circle->setRadius(this->_radius);
		this->_circle->setOrigin(this->_radius, this->_radius);
	}

	void CircleCollider::RenderDebug(sf::RenderWindow* i_window)
	{
		i_window->draw(*this->_circle);
	}

#pragma endregion

#pragma region Setters And Getters

	float CircleCollider::GetColliderRadius() const
	{
		return this->_radius;
	}

	Math::Point2D CircleCollider::GetColliderExtents()
	{
		return Math::Point2D(this->_radius, this->_radius);
	}

	void CircleCollider::SetColliderRadius(const float i_radius)
	{
		this->_radius = i_radius;
	}

	float CircleCollider::GetColliderNormalizedAngle()
	{
		return 0.0f;
	}

#pragma endregion
}
