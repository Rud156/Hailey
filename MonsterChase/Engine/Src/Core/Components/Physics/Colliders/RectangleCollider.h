#pragma once
#include "BaseCollider.h"
#include "../../../../Containers/WeakPtr.h"
#include "../../../BaseComponents/Node.h"

namespace sf
{
	class RenderWindow;
	class RectangleShape;
}

namespace Core::Components::Physics::Colliders
{
	class RectangleCollider final : public BaseCollider
	{
	private:
		Math::Point2D* _extents; // Extents is always half from the center
		sf::RectangleShape* _rect;

	public:
		// Constructor
		RectangleCollider();

		// Overridden Parent
		virtual ~RectangleCollider() override;
		void Ready(Containers::WeakPtr<BaseComponents::Node> i_node) override;
		virtual void SetupRender() override;
		virtual void RenderDebug(sf::RenderWindow* i_window) override;

		// Setters And Getters
		[[nodiscard]] Math::Point2D GetColliderExtents() override;
		void SetColliderExtents(float i_x, float i_y) const;
		void SetColliderExtents(Math::Point2D& i_point2d) const;
		[[nodiscard]] virtual float GetColliderNormalizedAngle() override;
	};
}
