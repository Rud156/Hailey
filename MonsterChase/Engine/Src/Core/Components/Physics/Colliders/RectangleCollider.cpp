#include "RectangleCollider.h"
#include "../../../../Maths/Point2D.h"
#include "../../../Components/Rendering/SpriteRenderer.h"
#include "../../../Components/Transform/Scale2D.h"
#include "../../../../Containers/PointerIncludes.cpp"

#include <SFML/Graphics.hpp>

namespace Core::Components::Physics::Colliders
{
#pragma region Constructor

	RectangleCollider::RectangleCollider()
	{
		this->_extents = new Math::Point2D();

		this->_rect = new sf::RectangleShape();
		this->_rect->setFillColor(sf::Color::Transparent);
		this->_rect->setOutlineColor(sf::Color::Red);
		this->_rect->setOutlineThickness(1);
	}

#pragma endregion

#pragma region Overridden Parent

	RectangleCollider::~RectangleCollider()
	{
		delete this->_extents;
		delete this->_rect;
	}

	void RectangleCollider::Ready(Containers::WeakPtr<BaseComponents::Node> i_node)
	{
		BaseCollider::Ready(i_node);

		this->_colliderType = ColliderType::Rectangle;
		Containers::WeakPtr<Rendering::SpriteRenderer> renderer =
			i_node.Lock()->GetComponent<Rendering::SpriteRenderer>();
		Containers::WeakPtr<Transform::Scale2D> scale2d =
			i_node.Lock()->GetComponent<Transform::Scale2D>();

		if (renderer)
		{
			const auto sprite = renderer.Lock()->GetSprite();
			const auto texture = sprite->getTexture();
			const auto textureSize = texture->getSize();
			auto x = static_cast<float>(textureSize.x);
			auto y = static_cast<float>(textureSize.y);

			if (scale2d)
			{
				x *= scale2d.Lock()->GetScale()->X();
				y *= scale2d.Lock()->GetScale()->Y();
			}

			this->_extents->set(static_cast<int>(x / 2.0f), static_cast<int>(y / 2.0f));
		}
	}

	void RectangleCollider::SetupRender()
	{
		this->_rect->setPosition(this->_center->X(), this->_center->Y());
		this->_rect->setSize(sf::Vector2f(this->_extents->X() * 2, this->_extents->Y() * 2));
		this->_rect->setOrigin(this->_extents->X(), this->_extents->Y());

		this->_rect->setRotation(this->_rotate2d->GetAngle());
	}

	void RectangleCollider::RenderDebug(sf::RenderWindow* i_window)
	{
		i_window->draw(*this->_rect);
	}

#pragma endregion

#pragma region Setters And Getters

	Math::Point2D RectangleCollider::GetColliderExtents()
	{
		return *this->_extents;
	}

	void RectangleCollider::SetColliderExtents(const float i_x, const float i_y) const
	{
		this->_extents->set(i_x, i_y);
	}

	void RectangleCollider::SetColliderExtents(Math::Point2D& i_point2d) const
	{
		this->_extents->set(i_point2d.X(), i_point2d.Y());
	}

	float RectangleCollider::GetColliderNormalizedAngle()
	{
		return this->_rotate2d->GetAngle();
	}

#pragma endregion
}
