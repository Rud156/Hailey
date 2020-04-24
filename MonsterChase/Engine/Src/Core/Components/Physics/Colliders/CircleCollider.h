#pragma once
#include "BaseCollider.h"
#include "../../../../Containers/WeakPtr.h"
#include "../../../BaseComponents/Node.h"

namespace sf
{
	class RenderWindow;
	class CircleShape;
}

namespace Core::Components::Physics::Colliders
{
	class CircleCollider final : public BaseCollider
	{
	private:
		float _radius;
		sf::CircleShape* _circle;

	public:
		// Constructor
		CircleCollider();

		// Overridden Parent
		virtual ~CircleCollider() override;
		void Ready(Containers::WeakPtr<BaseComponents::Node> i_node) override;
		virtual void SetupRender() override;
		virtual void RenderDebug(sf::RenderWindow* i_window) override;

		// Setters And Getters
		[[nodiscard]] float GetColliderRadius() const;
		[[nodiscard]] virtual Math::Point2D GetColliderExtents() override;
		void SetColliderRadius(float i_radius);
		[[nodiscard]] virtual float GetColliderNormalizedAngle() override;
	};
}
